#include "Worm.h"
#include "b2CircleShape.h"
#include "b2PolygonShape.h"
#include "b2Fixture.h"
#include "Protocol.h"
#include "WeaponFactory.h"
#include "Girder.h"
#include "Math.h"
#include <algorithm>

Worm::Worm(World& world, GameParameters& parameters, int id, int player_id):
	PhysicalObject(world, id, TYPE_WORM), player_id(player_id), life(parameters.getWormLife()), 
	dir(1), parameters(parameters), max_height(0), colliding_with_girder(0), friction(0), 
	movement_allowed(false), angle(0){
		this->changeWeapon(DEFAULT_WEAPON);
	}

Worm::~Worm(){}

void Worm::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
}

void Worm::createFixtures(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = worm_size / 2; 
		  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 10;
	this->body->CreateFixture(&fixtureDef);
	this->body->SetFixedRotation(true);

	//Sensor para colisiones
	b2PolygonShape sensorShape;
	sensorShape.SetAsBox(worm_size * 0.5 * 0.7, worm_size / 5, b2Vec2(0, -1 * worm_size / 2), 0); 
		  
	b2FixtureDef sensorFixtureDef;
	sensorFixtureDef.shape = &sensorShape;
	sensorFixtureDef.isSensor = true;
	this->body->CreateFixture(&sensorFixtureDef);
}

int Worm::getPlayerId() const{
	return this->player_id;
}

int Worm::getLife() const{
	return this->life;
}

char Worm::getDir() const{
	return this->dir;
}

bool Worm::isColliding() const{
	return this->colliding_with_girder;
}

const std::string& Worm::getCurrentWeapon() const{
	return ((Weapon*)weapon.get())->getName();
}

void Worm::addLife(int life){
	this->life += life;
}

void Worm::reduceLife(int damage){
	this->life -= damage;
	if (this->life <= 0){
		this->life = 0;
		this->is_dead = true;
	}
}

bool Worm::move(char action){
	if (!this->friction){
		return false;
	}
	if (action == MOVE_RIGHT){
		this->dir = action;
		b2Vec2 velocity(parameters.getWormVelocity(), 0);
		this->world.setLinearVelocity(*this, velocity);
	} else if (action == MOVE_LEFT){
		this->dir = action;
		b2Vec2 velocity(-1 * parameters.getWormVelocity(), 0);
		this->world.setLinearVelocity(*this, velocity);
	} else {
	
		this->movement_allowed = true;
		if (action == JUMP){
			b2Vec2 velocity(parameters.getWormJumpVelocity(), parameters.getWormJumpHeight());
			velocity.x *= this->dir;
			this->world.setLinearVelocity(*this, velocity);
		} else if (action == ROLLBACK){
			b2Vec2 velocity(parameters.getWormRollbackVelocity(), parameters.getWormRollbackHeight());
			velocity.x *= -1 * this->dir;
			this->world.setLinearVelocity(*this, velocity);
		}
	}
	return true;
}

void Worm::changeWeapon(const std::string& weapon){
	this->weapon.reset();
	WeaponFactory factory(this->world, this->parameters);
	this->weapon = factory.getWeapon(weapon);
}

void Worm::shoot(int angle, int power, int time){
	b2Vec2 pos = this->getPosition();
	int shooter_id = this->id;
	float x_add = (worm_size * this->dir);;
	float y_add = worm_size;
	if (angle > MAX_WEAPON_ANGLE){
		shooter_id = -1;
		x_add *= Math::cosDegrees(this->angle);
		y_add *= Math::sinDegrees(this->angle);
	} else {
		float factor = (this->getCurrentWeapon() == BAT_NAME ? 0.2 : 0.7);
		x_add *= Math::cosDegrees(angle) * factor;
		y_add *= Math::sinDegrees(angle) * factor;
	}
	
	pos.x += x_add;
	pos.y += y_add;

	((Weapon*)this->weapon.get())->shoot(this->dir, angle, power, time, shooter_id);
	this->world.addObject(this->weapon, pos);
}

void Worm::shoot(b2Vec2 pos){
	((Weapon*)this->weapon.get())->shoot(*this, pos);
}

void Worm::receiveWeaponDamage(int damage, const b2Vec2 &epicenter){
	this->reduceLife(damage);
	b2Vec2 direction = this->body->GetPosition() - epicenter;
	direction.Normalize();
	this->body->SetGravityScale(1);
	this->movement_allowed = true;
	this->body->SetLinearVelocity(damage * parameters.getWormExplosionVelocity() * direction);
}

void Worm::collideWithSomething(CollisionData *other){
	if (other->getType() == TYPE_BORDER){
		this->kill();
	} else if(other->getType() == TYPE_GIRDER){
		int min_height = parameters.getWormHeightToDamage();
		float current_height = this->body->GetPosition().y;
		this->max_height -= current_height;
		
		if (this->max_height >= min_height){
			this->reduceLife(std::min((int) this->max_height - min_height, parameters.getWormMaxHeightDamage()));
		}
		this->max_height = 0;
		this->colliding_with_girder ++;
		Girder* girder = (Girder*)other->getObject();
		if (girder->hasFriction()){
			this->friction++;
			this->movement_allowed = false;
			this->angle = girder->getAngle();
		}
	}
}

void Worm::endCollissionGirder(char has_friction){
	this->friction -= has_friction;
	this->colliding_with_girder --;
	if (this->friction <= 0){
		this->friction = 0;
		this->body->SetGravityScale(1);
		this->angle = 0;
	}
}

bool Worm::isActive(){
	if (!this->colliding_with_girder){
		float height = this->body->GetPosition().y;
		this->max_height = std::max(this->max_height, height);
	} else if (this->friction && !this->movement_allowed){
		this->body->SetGravityScale(0);
		this->body->SetLinearVelocity(b2Vec2(0, 0));
	}
	if (!this->body->IsAwake()){
		this->movement_allowed = false;
	}
	return PhysicalObject::isActive();
}

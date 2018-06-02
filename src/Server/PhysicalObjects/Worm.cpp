#include "Worm.h"
#include "b2PolygonShape.h"
#include "b2Fixture.h"
#include "Protocol.h"
#include "WeaponFactory.h"
#include "Girder.h"
#include "Math.h"
#include <algorithm>

Worm::Worm(World& world, GameParameters& parameters, int id, int player_id):
	PhysicalObject(world, id, TYPE_WORM), player_id(player_id), life(parameters.getWormLife()), 
	dir(1), parameters(parameters), max_height(0), colliding_with_girder(0), friction(0), angle(0){
		this->changeWeapon(DEFAULT_WEAPON);
	}

Worm::~Worm(){}

void Worm::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
}

void Worm::createFixtures(){
	b2PolygonShape boxShape;
	boxShape.SetAsBox(worm_size / 2, worm_size / 2);
		  
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 10;
	this->body->CreateFixture(&boxFixtureDef);
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
	return this->colliding_with_girder > 0;
}

const std::string& Worm::getCurrentWeapon() const{
	return ((Weapon*)weapon.get())->getName();
}

void Worm::addLife(int life){
	this->life += life;
}

void Worm::reduce_life(int damage){
	this->life -= damage;
	if (this->life <= 0){
		this->life = 0;
		this->is_dead = true;
	}
}

bool Worm::move(char action){
	if (!this->colliding_with_girder){
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
	
		this->friction = 0;
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
	((Weapon*)this->weapon.get())->shoot(this->dir, angle, power, time);
	b2Vec2 pos = this->getPosition();
	if (angle > MAX_WEAPON_ANGLE){
		angle = this->angle;
	}
	pos.x += (worm_size * Math::cosDegrees(angle) * this->dir);
	pos.y += (worm_size * Math::sinDegrees(angle));

	this->world.addObject(this->weapon, pos);
}

void Worm::shoot(b2Vec2 pos){
	((Weapon*)this->weapon.get())->shoot(*this, pos);
}

void Worm::receive_weapon_damage(int damage, const b2Vec2& epicenter){
	this->reduce_life(damage);
	b2Vec2 direction = this->body->GetPosition() - epicenter;
	direction.Normalize();
	this->body->SetGravityScale(1);
	this->friction = 0;
	this->body->SetLinearVelocity(damage * parameters.getWormExplosionVelocity() * direction);
}

void Worm::collide_with_something(CollisionData* other){
	if (other->getType() == TYPE_BORDER){
		this->kill();
	} else if(other->getType() == TYPE_GIRDER){
		int min_height = parameters.getWormHeightToDamage();
		float current_height = this->body->GetPosition().y;
		this->max_height -= current_height;
		
		if (this->max_height >= min_height){
			this->reduce_life(std::min((int)this->max_height - min_height, parameters.getWormMaxHeightDamage()));
		}
		this->colliding_with_girder++;
		this->max_height = 0;
		Girder* girder = (Girder*)other->getObject();
		this->angle = girder->getAngle();
		if (girder->has_friction()){
			this->friction++;
		}
	}
}

void Worm::end_collission_girder(char has_friction){
	this->colliding_with_girder--;
	this->friction -= has_friction;
	if (this->friction <= 0){
		this->friction = 0;
		this->body->SetGravityScale(1);
	}
	if(this->colliding_with_girder == 0){
		this->angle = 0;
	}
}

bool Worm::isActive(){
	if (!this->colliding_with_girder){
		float height = this->body->GetPosition().y;
		this->max_height = std::max(this->max_height, height);
	}
	if (this->friction){
		this->body->SetGravityScale(0);
		this->body->SetLinearVelocity(b2Vec2(0, 0));
	}
	return PhysicalObject::isActive();
}

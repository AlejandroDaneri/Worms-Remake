#include "Weapon.h"
#include "b2Fixture.h"
#include "b2CircleShape.h"
#include "CollisionData.h"
#include "Worm.h"
#include "Math.h"

int Weapon::weapon_id = 1;

Weapon::Weapon(World& world, GameParameters& parameters, int damage, int radius): 
	PhysicalObject(world, Weapon::weapon_id++, TYPE_WEAPON), parameters(parameters), 
	damage(damage), radius(radius), 
	waiting_to_explode(false), time_to_explode(-1), angle(MAX_WEAPON_ANGLE + 1), power(-1),
	shooter_id(-1), explode_time(world, *this){}

Weapon::~Weapon(){
	this->explode_time.join();
}

bool Weapon::isActive(){
	return this->waiting_to_explode || PhysicalObject::isActive();
}

void Weapon::shoot(char dir, int angle, int power, int time, int shooter_id){
	if (dir == -1 && angle <= MAX_WEAPON_ANGLE){
		angle = 180 - angle;
	}
	this->time_to_explode = time;
	this->angle = angle;
	this->power = power;
	this->shooter_id = shooter_id;
}

void Weapon::shoot(Worm& shooter, b2Vec2 pos){}

void Weapon::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
	body_def.fixedRotation = true;
	body_def.bullet = true;
}

void Weapon::createFixtures(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = weapon_size / 2; 
		  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 4;
	this->body->CreateFixture(&fixtureDef);
}

void Weapon::setInitialVelocity(){
	if (this->angle <= 180){
		int velocity = this->parameters.getWeaponsVelocity();
		if (this->power != -1){
			 velocity *= this->power / 1000;
		}
		b2Vec2 linear_velocity(velocity * Math::cosDegrees(this->angle), velocity * Math::sinDegrees(this->angle));
		this->body->SetLinearVelocity(linear_velocity);
	}
	this->waiting_to_explode = true;
	this->explode_time.setTime(this->time_to_explode);
	this->explode_time.start();
}


void Weapon::explode(){
	b2Vec2 center = this->body->GetPosition();
	for (float bullet_angle = 0; bullet_angle < 360; bullet_angle+= 5){
		this->attackWormExplosion(center, bullet_angle);
	}
	
	this->explode_time.stop();
	this->waiting_to_explode = false;
	this->is_dead = true;
}

void Weapon::attackWormExplosion(const b2Vec2& center, int angle){
	b2Vec2 end = center + this->radius * b2Vec2(Math::cosDegrees(angle), Math::sinDegrees(angle));
	b2Body* closest_body = this->world.getClosestObject(&this->explosion, center, end);
	if (closest_body){
		Worm* worm = (Worm*)((CollisionData*)closest_body->GetUserData())->getObject();
		float distance = b2Distance(center, worm->getPosition());
		int worm_damage = this->damage * (1 - distance / (2 * this->radius)); //Justo en el borde hace la mitad de danio
		worm->receiveWeaponDamage(worm_damage, center);
	}
}

void Weapon::collideWithSomething(CollisionData *other){
	if (this->time_to_explode == -1){
		this->explode_time.stop();
		this->explode();
	} else if (other->getType() == TYPE_BORDER){
		this->explode_time.stop();
		this->is_dead = true;
	}
}

int Weapon::getShooterId() const{
	return this->shooter_id;
}

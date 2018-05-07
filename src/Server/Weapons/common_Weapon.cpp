#include "Weapon.h"
#include <cmath>
#include "b2Fixture.h"
#include "b2CircleShape.h"

Weapon::Weapon(World& world, int id, int radius, int damage, int default_velocity): 
	PhysicalObject(world, id, "Weapon"), explosion(radius, damage), default_velocity(default_velocity), waiting_to_explode(false){}

Weapon::~Weapon(){}

bool Weapon::isMoving(){
	if (this->waiting_to_explode){
		return true;
	}
	return PhysicalObject::isMoving();
}

void Weapon::shoot(int angle, int power, int time){
	this->time_to_explode = time;
	this->angle = angle;
	this->power = power;
}

void Weapon::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
	body_def.fixedRotation = true;
}

void Weapon::createFixtures(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = 1; //radius
		  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 4;
	this->body->CreateFixture(&fixtureDef);
}

void Weapon::setInitialVelocity(){
	if (angle != -1){
		int velocity = this->default_velocity;
		if (power != -1){
			 velocity += this->power;
		}
		b2Vec2 linear_velocity(velocity * cos(angle), velocity * sin(angle));
		this->body->SetLinearVelocity(linear_velocity);
	}
}

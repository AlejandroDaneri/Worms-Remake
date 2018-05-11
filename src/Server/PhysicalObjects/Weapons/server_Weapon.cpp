#include "Weapon.h"
#include "b2Fixture.h"
#include "b2CircleShape.h"
#include "Worm.h"
#include <cmath>

#define PI 3.14159265
#define RADIANS PI / 180

int Weapon::id = 1;

Weapon::Weapon(World& world, GameParameters& parameters, int damage, int radius, int ricochets): 
	PhysicalObject(world, Weapon::id, "Weapon"), parameters(parameters), 
	damage(damage), radius(radius), 
	waiting_to_explode(false), ricochets(ricochets){}

Weapon::~Weapon(){}

bool Weapon::isActive(){
	return this->waiting_to_explode || PhysicalObject::isActive();
}

void Weapon::shoot(int angle, int power, int time){
	this->time_to_explode = time;
	this->angle = angle;
	this->power = power;
}

void Weapon::shoot(Worm& shooter, b2Vec2 pos){}

void Weapon::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
	body_def.fixedRotation = true;
}

void Weapon::createFixtures(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = 0.5; //radius
		  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 4;
	this->body->CreateFixture(&fixtureDef);
}

void Weapon::setInitialVelocity(){
	if (this->angle < 500){
		int velocity = this->parameters.getWeaponsVelocity();
		if (this->power != -1){
			 velocity *= this->power;
		}
		this->angle *= RADIANS;
		b2Vec2 linear_velocity(velocity * cos(angle), velocity * sin(angle));
		this->body->SetLinearVelocity(linear_velocity);
	}
	this->waiting_to_explode = true;
	///Thread time
}

void Weapon::explode(){
	for (int i = 0; i < 360; i+= 20){
		///////////////////////////////////////////
	}
	//stop thread time
	this->waiting_to_explode = false;
	this->is_dead = true;
}

void Weapon::collide_with_something(CollisionData* other){
	if (this->time_to_explode == -1){
		this->explode();
	}
}

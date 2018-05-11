#include "Bullet.h"
#include "b2Fixture.h"
#include "b2CircleShape.h"
#include <cmath>

#define PI 3.14159265
#define RADIANS PI / 180

#include <iostream>//////////////////////////////////////////////////////////////////////////////////////////////

Bullet::Bullet(World& world, int angle, int damage, int radius, b2Vec2 epicenter): 
	PhysicalObject(world, 0, "Bullet"), angle(angle), damage(damage), radius(radius), epicenter(epicenter){}

Bullet::~Bullet(){}

void Bullet::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_kinematicBody;
	body_def.position.Set(pos.x, pos.y);
	body_def.fixedRotation = true;
}

bool Bullet::isDead(){
	float distance = b2Distance(this->body->GetPosition(), this->epicenter);
	std::cout<<"Bullet is dead? distance= "<<distance<<std::endl;
	return PhysicalObject::isDead() || distance >= this->radius;
}

void Bullet::createFixtures(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = 0.5; //radius
		  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 4;
	this->body->CreateFixture(&fixtureDef);
}
void Bullet::setInitialVelocity(){
	int velocity = 10;
	float angle = this->angle * RADIANS;
	b2Vec2 linear_velocity(velocity * cos(angle), velocity * sin(angle));
	this->body->SetLinearVelocity(linear_velocity);
}

void Bullet::collide_with_something(CollisionData* other){
	std::cout<<"Bullet collision with: "<<other->getType()<<std::endl;
	if (other->getType() == "Worm"){
		Worm* worm = (Worm*) other->getObject();
		float distance = b2Distance(this->body->GetPosition(), this->epicenter);
		std::cout<<"  distance: "<<distance<<std::endl;

		int worm_damage = this->damage * (1 - distance / (2 * this->radius)); //Justo en el borde hace la mitad de danio
		worm->reduce_life(worm_damage);
	}
	this->is_dead = true;
}

b2Vec2 Bullet::getEpicenter(){
	b2Vec2 epicenter = this->epicenter;
	float angle = this->angle * RADIANS;
	epicenter.x += 2 * cos(angle);
	epicenter.y += 2 * sin(angle);
	return this->epicenter;
}

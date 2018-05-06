#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(World& world): world(world), is_dead(false){}

PhysicalObject::~PhysicalObject(){}

void PhysicalObject::addToWorld(const b2Vec2& pos){
	b2BodyDef body_def;
	this->getBodyDef(body_def, pos);
	this->body = this->world.addObject(&body_def);
	/////////////this->body->SetUserData(this->getData());
	this->createFixtures();
}

b2Vec2 PhysicalObject::getPosition(){
	return this->body->GetPosition();
}

b2Body* PhysicalObject::getBody(){
	return this->body;
}

bool PhysicalObject::isMoving(){
	return this->body->IsAwake();
}

bool PhysicalObject::isDead(){
	return this->is_dead;
}

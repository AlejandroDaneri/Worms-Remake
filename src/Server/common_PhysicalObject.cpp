#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(World& world): world(world){}

PhysicalObject::~PhysicalObject(){}

void PhysicalObject::addToWorld(const b2Vec2& pos){
	this->body = this->world.addObject(this->getBodyDef(pos));
	/////////////this->body->SetUserData(this->getData());
	this->createFixtures();
}

b2Vec2 PhysicalObject::getPosition(){
	return this->body->GetPosition();
}

b2Body* PhysicalObject::getBody(){
	return this->body;
}

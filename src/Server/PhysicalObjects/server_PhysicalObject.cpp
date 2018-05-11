#include "PhysicalObject.h"
#include "World.h"

PhysicalObject::PhysicalObject(World& world, int id, std::string type):
	world(world), is_dead(false), id(id), type(type), last_position(-1, -1),
	collision_data(type, this){}

PhysicalObject::~PhysicalObject(){}

void PhysicalObject::initializeBody(b2Body* body){
	this->body = body;
	this->body->SetUserData(&this->collision_data);
	this->createFixtures();
	this->setInitialVelocity();
}

b2Vec2 PhysicalObject::getPosition(){
	return this->body->GetPosition();
}

b2Body* PhysicalObject::getBody(){
	return this->body;
}

bool PhysicalObject::isMoving(){
	b2Vec2 pos = this->body->GetPosition();
	bool moved = pos != this->last_position;
	this->last_position = pos;
	return moved;
}

bool PhysicalObject::isActive(){
	return this->body->IsAwake();
}

bool PhysicalObject::isDead(){
	return this->is_dead;
}

int PhysicalObject::getId(){
	return this->id;
}

std::string& PhysicalObject::getType(){
	return this->type;
}

void PhysicalObject::setInitialVelocity(){}

void PhysicalObject::collide_with_something(CollisionData* other){}

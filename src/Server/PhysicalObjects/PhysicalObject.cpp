#include "PhysicalObject.h"
#include "World.h"

PhysicalObject::PhysicalObject(World& world, int id, const std::string& type):
	world(world), body(NULL), is_dead(false), id(id), type(type), last_position(-1, -1),
	last_position_sended(false), collision_data(type, this){}

PhysicalObject::~PhysicalObject(){}

void PhysicalObject::initializeBody(b2Body* body){
	this->body = body;
	this->body->SetUserData(&this->collision_data);
	this->createFixtures();
	this->setInitialVelocity();
}

void PhysicalObject::destroyBody(){
	this->body = NULL;
}

b2Vec2 PhysicalObject::getPosition(){
	return this->body->GetPosition();
}

b2Body* PhysicalObject::getBody(){
	return this->body;
}

bool PhysicalObject::isMoving(){
	b2Vec2 pos = this->body->GetPosition();
	bool moved_x = (int)(pos.x * UNIT_TO_SEND) != (int)(this->last_position.x * UNIT_TO_SEND);
	bool moved_y = (int)(pos.y * UNIT_TO_SEND) != (int)(this->last_position.y * UNIT_TO_SEND);
	this->last_position = pos;
	bool moved = moved_x || moved_y;
	if (moved){
		this->last_position_sended = false;
		return true;
	}
	if (!this->body->IsAwake() && !this->last_position_sended){
		this->last_position_sended = true;
		return true;
	}
	return false;
}

bool PhysicalObject::isActive(){
	return this->body->IsAwake();
}

bool PhysicalObject::isDead(){
	return this->is_dead;
}

bool PhysicalObject::isWindAffected(){
	return false;
}

void PhysicalObject::kill(){
	this->is_dead = true;
}

int PhysicalObject::getId(){
	return this->id;
}

const std::string& PhysicalObject::getType(){
	return this->type;
}

void PhysicalObject::setInitialVelocity(){}

void PhysicalObject::collide_with_something(CollisionData* other){}

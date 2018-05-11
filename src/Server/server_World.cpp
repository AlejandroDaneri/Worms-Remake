#include "World.h"
#include "BottomBorder.h"

World::World(const b2Vec2& gravity): world(gravity), is_active(false){
	this->world.SetAllowSleeping(true);
	this->world.SetContinuousPhysics(true);
	this->world.SetContactListener(&this->collision_listener);
	this->initialize();
}
		
World::~World(){}


#include <iostream>//////////////////////////////////////////////////////////////////////////////
void World::run(){
	float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	while(this->running){
		std::this_thread::sleep_for(std::chrono::milliseconds(60));

		std::lock_guard<std::mutex> lock(this->mutex);
		this->world.Step(timeStep, velocityIterations, positionIterations);

		for (auto it = this->bullets_to_add.begin(); it != this->bullets_to_add.end(); it++){
			Bullet* bullet = (Bullet*)it->get();

			b2BodyDef body_def;
			bullet->getBodyDef(body_def, bullet->getEpicenter());
			bullet->initializeBody(this->world.CreateBody(&body_def));
			this->bullets.push_back(*it);
			std::cout<<"Bullet added"<<std::endl;
		}
		this->bullets_to_add.clear();

		this->is_active = false;

		auto it = this->bullets.begin();
		while(it != this->bullets.end()){
			if ((*it)->isDead()){
				this->removeObject(*it);
				it = this->bullets.erase(it);
				std::cout<<"Bullet removed"<<std::endl;
			} else {
				this->is_active = true;
				++it;
			}
		}
		for (auto it = this->objects.begin(); it != this->objects.end(); it++){
			if ((*it)->isDead()){
				this->removeObject(*it);
			} else if ((*it)->isActive()){
				this->is_active = true;
			}
		}
	}
}

bool World::isActive(){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->is_active;
}

void World::addBullet(physical_object_ptr bullet){
	this->bullets_to_add.push_back(bullet);
}

void World::addObject(physical_object_ptr object, const b2Vec2& pos){
	b2BodyDef body_def;
	object->getBodyDef(body_def, pos);

	std::lock_guard<std::mutex> lock(this->mutex);
	object->initializeBody(this->world.CreateBody(&body_def));
	if (body_def.type != b2_staticBody){
		this->objects.push_back(object);
	} else {
		this->girders.push_back(object);
	}
}

void World::removeObject(physical_object_ptr object){
	this->world.DestroyBody(object->getBody());
}

void World::initialize(){
	physical_object_ptr bottom_border(new BottomBorder(*this));
	this->addObject(bottom_border, b2Vec2(-50000, 4));///////////////////////////////////////////////////////////ver
}

b2Vec2 World::getObjectPosition(PhysicalObject& object){
	std::lock_guard<std::mutex> lock(this->mutex);
	return object.getBody()->GetPosition();
}

void World::setLinearVelocity(PhysicalObject& object, b2Vec2& velocity){
	std::lock_guard<std::mutex> lock(this->mutex);
	b2Body* body = object.getBody();
	//body->ApplyLinearImpulse(velocity, body->GetWorldCenter(), true);
	body->SetLinearVelocity(velocity);
}

std::list<physical_object_ptr>& World::getObjectsList(){
	return this->objects;
}

std::mutex& World::getMutex(){
	return this->mutex;
}

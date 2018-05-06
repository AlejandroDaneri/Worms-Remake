#include "World.h"

World::World(const b2Vec2& gravity): world(gravity){
	this->world.SetAllowSleeping(true);
	this->world.SetContinuousPhysics(true);
	/////////////////this->world->SetContactListener(&colission);
}
		
World::~World(){}

void World::run(){
	while(this->running){
		float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
		int32 velocityIterations = 8;   //how strongly to correct velocity
		int32 positionIterations = 3;   //how strongly to correct position
		std::this_thread::sleep_for (std::chrono::milliseconds(15));

		std::lock_guard<std::mutex> lock(this->mutex);
		this->world.Step(timeStep, velocityIterations, positionIterations);
	}
}

b2Body* World::addObject(const b2BodyDef* def){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->world.CreateBody(def);
}

void World::removeObject(PhysicalObject& object){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->world.DestroyBody(object.getBody());
}

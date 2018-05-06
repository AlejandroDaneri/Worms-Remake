#include "World.h"
#include "BottomBorder.h"

World::World(const b2Vec2& gravity): world(gravity){
	this->world.SetAllowSleeping(true);
	this->world.SetContinuousPhysics(true);
	/////////////////this->world->SetContactListener(&colission);
	this->initialize();
}
		
World::~World(){}

void World::run(){
	float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	while(this->running){
		std::this_thread::sleep_for(std::chrono::milliseconds(15));

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

void World::initialize(){
	BottomBorder bottom_border(*this);
	bottom_border.addToWorld(b2Vec2(0, 900));///////////////////////////////////////////////////////////ver
}

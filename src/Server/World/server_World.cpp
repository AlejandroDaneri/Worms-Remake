#include "World.h"
#include "Weapon.h"
#include "BottomBorder.h"
#include "b2WorldCallbacks.h"
#include "RayCastClosestCallback.h"
#include "server_Fragment.h"

World::World(GameParameters& parameters): world(b2Vec2(0, parameters.getGravity())),
	wind(parameters), is_active(false){
	this->world.SetAllowSleeping(true);
	this->world.SetContinuousPhysics(true);
	this->world.SetContactListener(&this->collision_listener);
	this->world.SetContactFilter(&this->collision_listener);
	this->initialize();
}
		
World::~World(){}

void World::run(){
	float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	while(this->running){
		for (auto it = this->fragments_to_add.begin(); it != this->fragments_to_add.end(); it++){
			Fragment* fragment = (Fragment*)it->get();
			this->addObject(*it, fragment->get_shoot_position());
		}
		this->fragments_to_add.clear();

		std::this_thread::sleep_for(std::chrono::milliseconds(60));

		std::lock_guard<std::mutex> lock(this->mutex);
		this->world.Step(timeStep, velocityIterations, positionIterations);

		this->is_active = false;
		for (auto it = this->objects.begin(); it != this->objects.end(); it++){
			if ((*it)->isDead()){
				this->removeObject(*it);
			} else if ((*it)->isActive()){
				this->is_active = true;
				if ((*it)->isWindAffected()){
					////(*it)->getBody()->ApplyForceToCenter(b2Vec2(this->wind.getVelocity(), 0), false);  ////////////elimino el viento por ahora
				}
			}
		}
	}
}

bool World::isActive(){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->is_active;
}

void World::update(){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->wind.update();
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

void World::addWeaponFragment(physical_object_ptr fragment){
	this->fragments_to_add.push_back(fragment);
}

void World::removeTimedWeapon(Weapon& weapon){
	this->world.DestroyBody(weapon.getBody());
}

void World::removeObject(physical_object_ptr object){
	b2Body* body = object->getBody();
	if (body){
		this->world.DestroyBody(object->getBody());
	}
}

void World::initialize(){
	physical_object_ptr bottom_border(new BottomBorder(*this));
	this->addObject(bottom_border, b2Vec2(-50000, 4));
}

b2Vec2 World::getObjectPosition(PhysicalObject& object){
	std::lock_guard<std::mutex> lock(this->mutex);
	return object.getBody()->GetPosition();
}

void World::setLinearVelocity(PhysicalObject& object, b2Vec2& velocity){
	std::lock_guard<std::mutex> lock(this->mutex);
	b2Body* body = object.getBody();
	//body->ApplyLinearImpulse(velocity, body->GetWorldCenter(), true);////////////////////
	body->SetLinearVelocity(velocity);
}

b2Body* World::getClosestObject(b2Vec2 center, b2Vec2 end, b2Vec2& normal){
	RayCastClosestCallback callback;
	this->world.RayCast(&callback, center, end);
	normal = callback.getClosestNormal();
	return callback.getClosestBody();
}

std::list<physical_object_ptr>& World::getObjectsList(){
	return this->objects;
}

std::list<physical_object_ptr>& World::getGirdersList(){
	return this->girders;
}

std::mutex& World::getMutex(){
	return this->mutex;
}

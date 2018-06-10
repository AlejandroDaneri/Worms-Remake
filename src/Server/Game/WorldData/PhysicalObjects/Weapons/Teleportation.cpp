#include "Teleportation.h"
#include "Worm.h"
#include <mutex>
#include <string>

Teleportation::Teleportation(World& world, GameParameters& parameters):
	Weapon(world, parameters, 0){}
		
Teleportation::~Teleportation(){}

const std::string& Teleportation::getName(){
	return TELEPORT_NAME;
}

void Teleportation::shoot(char dir, int angle, int power,
								int time, int shooter_id){}

void Teleportation::shoot(Worm& shooter, b2Vec2 pos){
	pos.x += (worm_size / 2);
	pos.y += (worm_size / 2);
	std::lock_guard<std::mutex> lock(this->world.getMutex());
	b2Body* body = shooter.getBody();
	if (body){
		shooter.getBody()->SetTransform(pos, 0);
		shooter.getBody()->SetAwake(true);
	}
}

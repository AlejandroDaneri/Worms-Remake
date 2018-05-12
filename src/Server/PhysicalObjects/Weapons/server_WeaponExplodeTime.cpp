#include "WeaponExplodeTime.h"
#include "Weapon.h"
#include "World.h"

WeaponExplodeTime::WeaponExplodeTime(World& world, Weapon& weapon): 
	weapon(weapon), world(world), time(-1){}

WeaponExplodeTime::~WeaponExplodeTime(){}

void WeaponExplodeTime::setTime(int time){
	this->time = time;
}

void WeaponExplodeTime::run(){
	if (this->time > 0){
		int passed = 0;
		while (this->running && passed < this->time){
			std::this_thread::sleep_for(std::chrono::seconds(1));
			passed++;
		}
		if (this->running){
			std::lock_guard<std::mutex> lock(this->world.getMutex());
			this->weapon.explode();
			this->world.removeTimedWeapon(this->weapon);
		}
	}

}
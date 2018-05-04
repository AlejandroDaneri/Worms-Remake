#include "Bazooka.h"

Bazooka::Bazooka(): DistanceWeapon(Bazooka::munitions, Bazooka::radius, Bazooka::damage){}

Bazooka::~Bazooka(){}
		
bool Bazooka::isTimed(){
	return false;
}
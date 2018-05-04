#include "Banana.h"

Banana::Banana(): DistanceWeapon(Banana::munitions, Banana::radius, Banana::damage){}

Banana::~Banana(){}
		
bool Banana::isTimed(){
	return true;
}
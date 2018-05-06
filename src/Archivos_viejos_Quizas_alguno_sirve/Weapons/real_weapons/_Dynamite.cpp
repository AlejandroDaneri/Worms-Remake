#include "Dynamite.h"

Dynamite::Dynamite(): MeleeWeapon(Dynamite::munitions, Dynamite::radius, Dynamite::damage){}

Dynamite::~Dynamite(){}
		
bool Dynamite::isTimed(){
	return true;
}
		
bool Dynamite::hasScope(){
	return false;
}
#include "Bat.h"

Bat::Bat(): MeleeWeapon(Bat::munitions, Bat::radius, Bat::damage){}

Bat::~Bat(){}
		
bool Bat::isTimed(){
	return false;
}
		
bool Bat::hasScope(){
	return true;
}
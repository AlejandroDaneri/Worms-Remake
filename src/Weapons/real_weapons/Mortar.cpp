#include "Mortar.h"

Mortar::Mortar(): FragmentableWeapon(Mortar::fragments, Mortar::munitions, Mortar::radius, Mortar::damage){}

Mortar::~Mortar(){}

bool Mortar::isTimed(){
	return false;
}

weapon_ptr Mortar::getFragment(){
	return weapon_ptr(new Mortar::Fragment());
}

Mortar::Fragment::Fragment(): DistanceWeapon(1, Mortar::Fragment::radius, Mortar::Fragment::damage){}

Mortar::Fragment::~Fragment(){}

bool Mortar::Fragment::isTimed(){
	return false;
}
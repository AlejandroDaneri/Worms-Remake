#include "RedGrenade.h"

RedGrenade::RedGrenade(): FragmentableWeapon(RedGrenade::fragments, RedGrenade::munitions, RedGrenade::radius, RedGrenade::damage){}

RedGrenade::~RedGrenade(){}

bool RedGrenade::isTimed(){
	return true;
}

weapon_ptr RedGrenade::getFragment(){
	return weapon_ptr(new RedGrenade::Fragment());
}

RedGrenade::Fragment::Fragment(): DistanceWeapon(1, RedGrenade::Fragment::radius, RedGrenade::Fragment::damage){}

RedGrenade::Fragment::~Fragment(){}

bool RedGrenade::Fragment::isTimed(){
	return false;
}
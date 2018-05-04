#include "HolyGrenade.h"

HolyGrenade::HolyGrenade(): DistanceWeapon(HolyGrenade::munitions, HolyGrenade::radius, HolyGrenade::damage){}

HolyGrenade::~HolyGrenade(){}
		
bool HolyGrenade::isTimed(){
	return true;
}
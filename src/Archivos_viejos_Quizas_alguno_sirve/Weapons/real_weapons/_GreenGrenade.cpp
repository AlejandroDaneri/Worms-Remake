#include "GreenGrenade.h"

GreenGrenade::GreenGrenade(): DistanceWeapon(GreenGrenade::munitions, GreenGrenade::radius, GreenGrenade::damage){}

GreenGrenade::~GreenGrenade(){}
		
bool GreenGrenade::isTimed(){
	return true;
}
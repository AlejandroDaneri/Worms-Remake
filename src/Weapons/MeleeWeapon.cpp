#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int munitions, int radius, int damage): Weapon(munitions, radius, damage){}
		
MeleeWeapon::~MeleeWeapon(){}

Position MeleeWeapon::getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power){
	return origin;
}

bool MeleeWeapon::hasVariablePower(){
	return false;
}

bool MeleeWeapon::isSelfDirected(){
	return false;
}
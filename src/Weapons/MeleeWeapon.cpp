#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(bool scope, bool timed, int radius, int damage):
	Weapon(scope, true, timed, false, radius, damage){}
		
MeleeWeapon::~MeleeWeapon(){}

Position MeleeWeapon::getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power){
	return origin;
}
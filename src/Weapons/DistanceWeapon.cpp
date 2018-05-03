#include "DistanceWeapon.h"

DistanceWeapon::DistanceWeapon(bool timed, int radius, int damage):
	Weapon(true, true, timed, false, radius, damage){}
		
DistanceWeapon::~DistanceWeapon(){}

Position DistanceWeapon::getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power){

	//Hacer algo para obtener el epicentro en base a pos, dir, angle power



	return Position(1,1);/////////////////////////////////////////////////////////////////////////
}

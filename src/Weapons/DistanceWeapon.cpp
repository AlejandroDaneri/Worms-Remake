#include "DistanceWeapon.h"

DistanceWeapon::DistanceWeapon(int munitions, int radius, int damage): Weapon(munitions, radius, damage){}
		
DistanceWeapon::~DistanceWeapon(){}

Position DistanceWeapon::getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power){

	//Hacer algo para obtener el epicentro en base a pos, dir, angle power



	return Position(1,1);/////////////////////////////////////////////////////////////////////////
}

bool DistanceWeapon::hasScope(){
	return true;
}

bool DistanceWeapon::hasVariablePower(){
	return true;
}

bool DistanceWeapon::isSelfDirected(){
	return false;
}

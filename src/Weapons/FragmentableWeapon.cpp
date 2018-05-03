#include "FragmentableWeapon.h"

FragmentableWeapon::FragmentableWeapon(int fragments, bool timed, int radius, int damage):
	DistanceWeapon(timed, radius, damage), fragments(fragments){}

FragmentableWeapon::~FragmentableWeapon(){}

void FragmentableWeapon::shoot(const Position& origin, const dir_ptr& dir, int angle, int power, int time){
	Position epicenter = this->getEpicenter(origin, dir, angle, power);
	this->radius.attack(epicenter, time);

	for (int i = 0; i < this->fragments; i++){
		weapon_ptr fragment = std::move(this->getFragment());
		fragment->shoot(epicenter, dir, angle, 0, 0);///////////////////////////////////////hacer angle y dir al azar////////////////////////////
	}
}
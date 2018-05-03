#include "SelfDirectedWeapon.h"

SelfDirectedWeapon::SelfDirectedWeapon(int radius, int damage):
	Weapon(false, false, false, true, radius, damage){}
		
SelfDirectedWeapon::~SelfDirectedWeapon(){}

Position SelfDirectedWeapon::getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power){
	throw std::runtime_error("No se puede usar este modo en un arma teledirigida");
}

void SelfDirectedWeapon::shoot(const Position& pos){
	this->radius.attack(pos, 0);
}
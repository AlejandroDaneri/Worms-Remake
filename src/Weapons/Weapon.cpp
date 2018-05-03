#include "Weapon.h"

Weapon::Weapon(int munitions, int radius, int damage): munitions(munitions), radius(radius, damage){}

Weapon::~Weapon(){}

void Weapon::shoot(const Position& origin, const dir_ptr& dir, int angle, int power, int time){
	Position epicenter = this->getEpicenter(origin, dir, angle, power);
	this->radius.attack(epicenter, time);
}

void Weapon::shoot(const Position& pos){
	throw std::runtime_error("No se puede usar este modo en un arma no teledirigida");
}

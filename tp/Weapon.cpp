#include "Weapon.h"

Weapon::Weapon(bool scope, bool variable_power, bool timed, int radius, int damage):
	scope(scope), variable_power(variable_power), timed(timed), radius(radius, damage){}

Weapon::~Weapon(){}

bool Weapon::hasScope(){
	return this->scope;
}

bool Weapon::hasVaraiblePower(){
	return this->variable_power;
}

bool Weapon::isTimed(){
	return this->timed;
}

void Weapon::shoot(int angle, int power, int time){
	throw std::runtime_error("Este arma no puede disparar en este modo");
}

void Weapon::shoot(const Position& pos){
	throw std::runtime_error("Este arma no puede disparar en este modo");
}

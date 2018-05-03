#include "Weapon.h"

Weapon::Weapon(bool scope, bool variable_power, bool timed, bool self_directed, int radius, int damage):
	scope(scope), variable_power(variable_power), timed(timed), 
	self_directed(self_directed), radius(radius, damage){}

Weapon::~Weapon(){}

bool Weapon::hasScope(){
	return this->scope;
}

bool Weapon::hasVariablePower(){
	return this->variable_power;
}

bool Weapon::isTimed(){
	return this->timed;
}

bool Weapon::isSelfDirected(){
	return this->self_directed;
}

void Weapon::shoot(const Position& origin, const dir_ptr& dir, int angle, int power, int time){
	Position epicenter = this->getEpicenter(origin, dir, angle, power);
	this->radius.attack(epicenter, time);
}

void Weapon::shoot(const Position& pos){
	throw std::runtime_error("No se puede usar este modo en un arma no teledirigida");
}

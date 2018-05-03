#include "SelfDirectedWeapon.h"

SelfDirectedWeapon::SelfDirectedWeapon(int munitions, int radius, int damage, int quantity): 
	Weapon(munitions, radius, damage), quantity(quantity){}
		
SelfDirectedWeapon::~SelfDirectedWeapon(){}

Position SelfDirectedWeapon::getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power){
	throw std::runtime_error("No se puede usar este modo en un arma teledirigida");
}

void SelfDirectedWeapon::shoot(const Position& pos){
	for (int i = 0; i < this->quantity; i++){
		this->radius.attack(pos, 0);
	}
}

bool SelfDirectedWeapon::hasScope(){
	return false;
}

bool SelfDirectedWeapon::hasVariablePower(){
	return false;
}

bool SelfDirectedWeapon::isTimed(){
	return false;
}

bool SelfDirectedWeapon::isSelfDirected(){
	return true;
}
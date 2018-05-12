#include "client_SelfDirectedWeapon.h"

SelfDirectedWeapon::SelfDirectedWeapon(std::string name, int ammo) : Weapon(name, ammo) {}
		
SelfDirectedWeapon::~SelfDirectedWeapon() {}

bool SelfDirectedWeapon::isSelfDirected(){
	return true;
}


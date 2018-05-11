#include "client_SelfDirectedWeapon.h"

SelfDirectedWeapon::SelfDirectedWeapon(std::string name, int ammo, int quantity) : Weapon(name, ammo),
	quantity(quantity) {}
		
SelfDirectedWeapon::~SelfDirectedWeapon(){}

/*Position SelfDirectedWeapon::getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power){
	throw std::runtime_error("No se puede usar este modo en un arma teledirigida");
}

void SelfDirectedWeapon::shoot(const Position& pos){
	for (int i = 0; i < this->quantity; i++){
		this->radius.attack(pos, 0);
	}
}*/

bool SelfDirectedWeapon::isSelfDirected(){
	return true;
}

void SelfDirectedWeapon::changeTime(int time) {}

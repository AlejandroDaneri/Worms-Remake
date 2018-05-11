#include "client_Bazooka.h"

Bazooka::Bazooka(int ammo) : DistanceWeapon(BAZOOKA_NAME, ammo, BAZOOKA_DAMAGE, 
	BAZOOKA_RADIUS) {}

Bazooka::~Bazooka(){}


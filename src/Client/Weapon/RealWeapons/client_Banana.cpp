#include "client_Banana.h"

Banana::Banana(int ammo) : DistanceWeapon(BANANA_NAME, ammo, BANANA_DAMAGE,
	BANANA_RADIUS, DEFAULT_TIME){}

Banana::~Banana() {}


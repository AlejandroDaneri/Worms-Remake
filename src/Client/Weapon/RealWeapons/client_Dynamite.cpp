#include "client_Dynamite.h"

Dynamite::Dynamite(int ammo): MeleeWeapon(DYNAMITE_NAME, ammo, DYNAMITE_DAMAGE,
	DYNAMITE_RADIUS, false, DEFAULT_TIME) {}

Dynamite::~Dynamite() {}


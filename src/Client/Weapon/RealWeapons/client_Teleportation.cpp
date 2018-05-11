#include "client_Teleportation.h"
#include "client_Weapons_defs.h"

Teleportation::Teleportation(int ammo): SelfDirectedWeapon(TELEPORT_NAME, ammo,
	TELEPORT_QUANTITY) {}
		
Teleportation::~Teleportation(){}


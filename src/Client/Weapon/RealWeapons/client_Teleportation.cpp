#include "client_Teleportation.h"

Teleportation::Teleportation(int ammo): SelfDirectedWeapon(TELEPORT_NAME, ammo,
	TELEPORT_DAMAGE, TELEPORT_RADIUS, TELEPORT_QUANTITY) {}
		
Teleportation::~Teleportation(){}


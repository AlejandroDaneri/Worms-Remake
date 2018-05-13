#include "client_Teleportation.h"
#include "client_Weapons_defs.h"

Teleportation::Teleportation(int ammo): SelfDirectedWeapon(TELEPORT_NAME, ammo) {}
		
Teleportation::~Teleportation(){}

Teleportation::Teleportation(Teleportation&& other) : SelfDirectedWeapon(std::move(other)) {}


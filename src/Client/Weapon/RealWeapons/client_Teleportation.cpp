#include "client_Teleportation.h"
#include "WeaponNames.h"

Teleportation::Teleportation(int ammo): SelfDirectedWeapon(TELEPORT_NAME, ammo) {}
		
Teleportation::~Teleportation(){}

Teleportation::Teleportation(Teleportation&& other) : SelfDirectedWeapon(std::move(other)) {}


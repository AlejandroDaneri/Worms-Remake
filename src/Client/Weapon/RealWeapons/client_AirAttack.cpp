#include "client_AirAttack.h"
#include "client_Weapons_defs.h"

AirAttack::AirAttack(int ammo) : SelfDirectedWeapon(AIR_ATTACK_NAME, ammo) {}
		
AirAttack::~AirAttack() {}

AirAttack::AirAttack(AirAttack&& other) : SelfDirectedWeapon(std::move(other)) {}


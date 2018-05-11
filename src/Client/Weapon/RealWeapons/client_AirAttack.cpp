#include "client_AirAttack.h"
#include "client_Weapons_defs.h"

AirAttack::AirAttack(int ammo) : SelfDirectedWeapon(AIR_ATTACK_NAME,
	ammo, AIR_ATTACK_MISSIL) {}
		
AirAttack::~AirAttack(){}


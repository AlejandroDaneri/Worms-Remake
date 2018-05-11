#include "client_AirAttack.h"

AirAttack::AirAttack(int ammo) : SelfDirectedWeapon(AIR_ATTACK_NAME,
	ammo, AIR_ATTACK_DAMAGE, AIR_ATTACK_RADIUS, AIR_ATTACK_MISSIL) {}
		
AirAttack::~AirAttack(){}


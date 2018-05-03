#include "AirAttack.h"

AirAttack::AirAttack(): SelfDirectedWeapon(AirAttack::munitions, AirAttack::radius, AirAttack::damage, AirAttack::missiles){}
		
AirAttack::~AirAttack(){}
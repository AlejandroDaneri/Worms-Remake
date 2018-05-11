#ifndef __CLIENTAIRATTACK_H__
#define __CLIENTAIRATTACK_H__

#include "client_SelfDirectedWeapon.h"
#include "client_Weapons_defs.h"

class AirAttack: public SelfDirectedWeapon{
	public:
		AirAttack(int ammo = AIR_ATTACK_AMMO);
		~AirAttack();
};

#endif

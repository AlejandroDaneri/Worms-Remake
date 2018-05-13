#ifndef __CLIENTAIRATTACK_H__
#define __CLIENTAIRATTACK_H__

#include "client_SelfDirectedWeapon.h"

class AirAttack: public SelfDirectedWeapon {
	public:
		AirAttack(int ammo);
		~AirAttack();
		AirAttack(AirAttack&& other);
};

#endif

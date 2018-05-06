#ifndef __AIRATTACK_H__
#define __AIRATTACK_H__

#include "SelfDirectedWeapon.h"

class AirAttack: public SelfDirectedWeapon{
	public:
		static const int munitions = 2;
		static const int radius = 2;
		static const int damage = 40;
		static const int missiles = 6;

		AirAttack();
		~AirAttack();
};

#endif
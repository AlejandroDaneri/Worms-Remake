#ifndef __SERVERAIRATTACKMISSILE_H__
#define __SERVERAIRATTACKMISSILE_H__

#include "Weapon.h"

class AirAttackMissile: public Weapon{
	public:

		AirAttackMissile(World& world, GameParameters& parameters);
		~AirAttackMissile();

		std::string getName() override;

};

#endif

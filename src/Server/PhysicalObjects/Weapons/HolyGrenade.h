#ifndef __SERVERHOLYGRENADE_H__
#define __SERVERHOLYGRENADE_H__

#include "Weapon.h"

class HolyGrenade: public Weapon{
	public:

		HolyGrenade(World& world, GameParameters& parameters);
		~HolyGrenade();

		const std::string& getName() override;
};

#endif

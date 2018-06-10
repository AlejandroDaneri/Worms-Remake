#ifndef __SERVERGREENGRENADE_H__
#define __SERVERGREENGRENADE_H__

#include "Weapon.h"
#include <string>

class GreenGrenade: public Weapon{
	public:
		GreenGrenade(World& world, GameParameters& parameters);
		~GreenGrenade();

		const std::string& getName() override;
};

#endif

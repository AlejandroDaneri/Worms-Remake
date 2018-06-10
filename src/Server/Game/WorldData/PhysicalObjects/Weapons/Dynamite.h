#ifndef __SERVERDYNAMITE_H__
#define __SERVERDYNAMITE_H__

#include "Weapon.h"
#include <string>

class Dynamite: public Weapon{
	public:
		Dynamite(World& world, GameParameters& parameters);
		~Dynamite();

		const std::string& getName() override;
};

#endif

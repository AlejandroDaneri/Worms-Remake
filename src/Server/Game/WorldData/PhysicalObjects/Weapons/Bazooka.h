#ifndef __SERVERBAZOOKA_H__
#define __SERVERBAZOOKA_H__

#include "Weapon.h"

class Bazooka: public Weapon{
	public:

		Bazooka(World& world, GameParameters& parameters);
		~Bazooka();

		const std::string& getName() override;
		bool isWindAffected() override;

};

#endif

#ifndef __SERVERBANANA_H__
#define __SERVERBANANA_H__

#include "Weapon.h"

class Banana: public Weapon{
	protected:
		void createFixtures() override;
		
	public:

		Banana(World& world, GameParameters& parameters);
		~Banana();

		const std::string& getName() override;

};

#endif
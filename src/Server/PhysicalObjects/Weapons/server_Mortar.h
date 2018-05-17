#ifndef __SERVERMORTAR_H__
#define __SERVERMORTAR_H__

#include "FragmentableWeapon.h"

class Mortar: public FragmentableWeapon{
	public:

		Mortar(World& world, GameParameters& parameters);
		~Mortar();

		const std::string& getName() override;

		bool isWindAffected() override;
};

#endif
#ifndef __TELEPORTATION_H__
#define __TELEPORTATION_H__

#include "SelfDirectedWeapon.h"
#include <climits>

#ifndef INFINITE
#define INFINITE INT_MAX
#endif

class Teleportation: public SelfDirectedWeapon{
	public:
		static const int munitions = INFINITE;
		static const int radius = 0;
		static const int damage = 0;

		Teleportation();
		~Teleportation();
};

#endif
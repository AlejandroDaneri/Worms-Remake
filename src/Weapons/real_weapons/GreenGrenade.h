#ifndef __GREENGRENADE_H__
#define __GREENGRENADE_H__

#include "DistanceWeapon.h"
#include <climits>

#ifndef INFINITE
#define INFINITE INT_MAX
#endif

class GreenGrenade: public DistanceWeapon{
	public:
		static const int munitions = INFINITE;
		static const int radius = 2;
		static const int damage = 30;

		GreenGrenade();
		~GreenGrenade();

		bool isTimed();

};

#endif
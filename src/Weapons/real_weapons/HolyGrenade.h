#ifndef __HOLYGRENADE_H__
#define __HOLYGRENADE_H__

#include "DistanceWeapon.h"


class HolyGrenade: public DistanceWeapon{
	public:
		static const int munitions = 1;
		static const int radius = 8;
		static const int damage = 110;

		HolyGrenade();
		~HolyGrenade();

		bool isTimed();

};

#endif
#ifndef __BANANA_H__
#define __BANANA_H__

#include "DistanceWeapon.h"

class Banana: public DistanceWeapon{
	public:
		static const int munitions = 10;
		static const int radius = 4;
		static const int damage = 70;

		Banana();
		~Banana();

		bool isTimed();

};

#endif
#ifndef __BAZOOKA_H__
#define __BAZOOKA_H__

#include "DistanceWeapon.h"
#include <climits>

#ifndef INFINITE
#define INFINITE INT_MAX
#endif

class Bazooka: public DistanceWeapon{
	public:
		static const int munitions = INFINITE;
		static const int radius = 2;
		static const int damage = 50;

		Bazooka();
		~Bazooka();

		bool isTimed();

};

#endif
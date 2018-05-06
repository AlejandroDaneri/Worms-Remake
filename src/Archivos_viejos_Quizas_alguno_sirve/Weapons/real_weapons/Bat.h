#ifndef __BAT_H__
#define __BAT_H__

#include "MeleeWeapon.h"
#include <climits>

#ifndef INFINITE
#define INFINITE INT_MAX
#endif

class Bat: public MeleeWeapon{
	public:
		static const int munitions = INFINITE;
		static const int radius = 0;
		static const int damage = 10;

		Bat();
		~Bat();

		bool isTimed();
		bool hasScope();
};

#endif
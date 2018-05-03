#ifndef __DYNAMITE_H__
#define __DYNAMITE_H__

#include "MeleeWeapon.h"

class Dynamite: public MeleeWeapon{
	public:
		static const int munitions = 5;
		static const int radius = 4;
		static const int damage = 50;

		Dynamite();
		~Dynamite();

		bool isTimed();
		bool hasScope();
};

#endif
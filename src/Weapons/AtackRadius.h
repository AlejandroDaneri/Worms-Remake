#ifndef __ATACKRADIUS_H__
#define __ATACKRADIUS_H__

#include "Position.h"

class AtackRadius{
	private:
		int radius;
		int damage;

	public:
		AtackRadius(int radius, int damage);
		~AtackRadius();

		void attack(const Position& epicenter, int time);////////////////////lista_gusanos

};

#endif

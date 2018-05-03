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

		void atack(const Position& epicenter);////////////////////lista_gusanos

};

#endif

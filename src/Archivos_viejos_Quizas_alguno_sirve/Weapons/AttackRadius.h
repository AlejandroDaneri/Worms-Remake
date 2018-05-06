#ifndef __ATTACKRADIUS_H__
#define __ATTACKRADIUS_H__

#include "Position.h"

class AttackRadius{
	private:
		int radius;
		int damage;

	public:
		AttackRadius(int radius, int damage);
		~AttackRadius();

		void attack(const Position& epicenter, int time);////////////////////lista_gusanos

};

#endif

#ifndef __DIRECTIONRIGHT_H__
#define __DIRECTIONRIGHT_H__

#include "Direction.h"

class DirectionRight: public Direction{
	private:

	public:
		DirectionRight();
		~DirectionRight();

		dir_ptr opposite();

		void move(Position& pos, int speed);
};

#endif

#ifndef __DIRECTIONDOWN_H__
#define __DIRECTIONDOWN_H__

#include "Direction.h"

class DirectionDown: public Direction{
	private:

	public:
		DirectionDown();
		~DirectionDown();

		dir_ptr opposite();

		void move(Position& pos, float speed);
};

#endif
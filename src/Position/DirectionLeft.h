#ifndef __DIRECTIONLEFT_H__
#define __DIRECTIONLEFT_H__

#include "Direction.h"

class DirectionLeft: public Direction{
	private:

	public:
		DirectionLeft();
		~DirectionLeft();

		dir_ptr opposite();

		void move(Position& pos, float speed);
};

#endif
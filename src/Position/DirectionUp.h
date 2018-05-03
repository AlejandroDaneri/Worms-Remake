#ifndef __DIRECTIONUP_H__
#define __DIRECTIONUP_H__

#include "Direction.h"

class DirectionUp: public Direction{
	private:

	public:
		DirectionUp();
		~DirectionUp();

		dir_ptr opposite();

		void move(Position& pos, int speed);
};

#endif

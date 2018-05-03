#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include "Position.h"
#include <memory>

class Direction;
typedef std::unique_ptr<Direction> dir_ptr;

class Direction{
	private:

	public:
		Direction();
		~Direction();

		virtual dir_ptr opposite() = 0;

		virtual void move(Position& pos, float speed) = 0;
};

#endif

#ifndef __POSITION__H__
#define __POSITION__H__

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

typedef char dir_t;
typedef unsigned int speed_t;

class Position{
	private:
		int x;
		int y;

	public:
		Position(int x, int y);
		~Position();

		bool operator==(const Position& other);

		void move(dir_t direction, speed_t speed);

		int distanceTo(const Position& other);

};

#endif

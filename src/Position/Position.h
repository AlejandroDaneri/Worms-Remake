#ifndef __POSITION_H__
#define __POSITION_H__

class Position{
	private:
		int x;
		int y;

	public:
		Position(int x, int y);
		~Position();

		bool operator==(const Position& other);

		void moveHorizontal(int speed);

		void moveVertical(int speed);

		int distanceTo(const Position& other);

};

#endif

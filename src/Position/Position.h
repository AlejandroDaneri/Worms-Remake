#ifndef __POSITION_H__
#define __POSITION_H__

class Position{
	private:
		float x;
		float y;

	public:
		Position(float x, float y);
		~Position();

		bool operator==(const Position& other);

		void moveHorizontal(float speed);

		void moveVertical(float speed);

		float distanceTo(const Position& other);

};

#endif

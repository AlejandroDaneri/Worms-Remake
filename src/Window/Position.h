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

		float getX() const;

        float getY() const;

};

#endif

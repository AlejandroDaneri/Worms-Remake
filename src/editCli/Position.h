#ifndef __POSITION_H__
#define __POSITION_H__

class Position{
	private:
		int x;
		int y;

	public:
		Position(int x, int y);
		~Position();
		Position(const Position&);
		Position& operator=(const Position&);

		bool operator==(const Position& other);

		int getX() const;

        int getY() const;

};

#endif

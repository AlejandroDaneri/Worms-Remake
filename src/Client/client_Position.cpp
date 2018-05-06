#include <cmath>
#include "Position.h"

Position::Position(int x, int y): x(x), y(y){}
		
Position::~Position(){}

bool Position::operator==(const Position& other){
	return this->x == other.x && this->y == other.y;
}

int Position::getX() const{
	return this->x;
}

int Position::getY() const{
	return this->y;
}

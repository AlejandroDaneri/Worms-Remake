#include <cmath>
#include "Position.h"

Position::Position(float x, float y): x(x), y(y){}
		
Position::~Position(){}

bool Position::operator==(const Position& other){
	return this->x == other.x && this->y == other.y;
}

float Position::getX() const{
	return this->x;
}

float Position::getY() const{
	return this->y;
}

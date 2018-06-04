#include "Position.h"
#include <cmath>

#define FACTOR 100

Position::Position(float x, float y): x(x), y(y){}
		
Position::~Position(){}

bool Position::operator==(const Position& other){
	return (int)(this->x * FACTOR) == (int)(other.x * FACTOR) && (int)(this->y * FACTOR) == (int)(other.y * FACTOR);
}

float Position::getX() const{
	return this->x;
}

float Position::getY() const{
	return this->y;
}

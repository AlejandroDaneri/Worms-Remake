#include <cmath>
#include "Position.h"

Position::Position(int x, int y): x(x), y(y){}
		
Position::~Position(){}

Position::Position(const Position& other) {
	this->x = other.x;
	this->y = other.y;
}

Position& Position::operator=(const Position& other) {
	this->x = other.x;
	this->y = other.y;
	return *this;
}

bool Position::operator==(const Position& other){
	return this->x == other.x && this->y == other.y;
}

int Position::getX() const{
	return this->x;
}

int Position::getY() const{
	return this->y;
}

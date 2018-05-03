#include <cmath>
#include "Position.h"

Position::Position(int x, int y): x(x), y(y){}
		
Position::~Position(){}

bool Position::operator==(const Position& other){
	return this->x == other.x && this->y == other.y;
}

void Position::moveHorizontal(int speed){
	this->x += speed;
}

void Position::moveVertical(int speed){
	this->y += speed;
}

int Position::distanceTo(const Position& other){
	int x = pow(this->x - other.x, 2);
	int y = pow(this->y - other.y, 2);
	return sqrt(x + y);
}
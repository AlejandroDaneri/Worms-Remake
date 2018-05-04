#include <cmath>
#include "Position.h"

Position::Position(float x, float y): x(x), y(y){}
		
Position::~Position(){}

bool Position::operator==(const Position& other){
	return this->x == other.x && this->y == other.y;
}

void Position::moveHorizontal(float speed){
	this->x += speed;
}

void Position::moveVertical(float speed){
	this->y += speed;
}

float Position::distanceTo(const Position& other){
	float x = pow(this->x - other.x, 2);
	float y = pow(this->y - other.y, 2);
	return sqrt(x + y);
}
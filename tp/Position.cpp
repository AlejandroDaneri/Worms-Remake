#include <cmath>
#include "Position.h"

Position::Position(int x, int y): x(x), y(y){}
		
Position::~Position(){}

bool Position::operator==(const Position& other){
	return this->x == other.x && this->y == other.y;
}

void Position::move(dir_t direction, speed_t speed){
	switch (direction){
		case DIR_UP:
			this->y += speed;
			break;
		case DIR_DOWN:
			this->y -= speed;
			break;
		case DIR_LEFT:
			this->x += speed;
			break;
		case DIR_RIGHT:
			this->x -= speed;
			break;
	}
}

int Position::distanceTo(const Position& other){
	int x = pow(this->x - other.x, 2);
	int y = pow(this->y - other.y, 2);
	return sqrt(x + y);
}
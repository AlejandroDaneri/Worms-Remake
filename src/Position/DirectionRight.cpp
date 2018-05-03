#include "DirectionRight.h"
#include "DirectionLeft.h"

DirectionRight::DirectionRight(){}

DirectionRight::~DirectionRight(){}

dir_ptr DirectionRight::opposite(){
	return dir_ptr(new DirectionLeft());
}

void DirectionRight::move(Position& pos, float speed){
	pos.moveHorizontal(speed);
}

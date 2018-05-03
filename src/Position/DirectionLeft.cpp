#include "DirectionRight.h"
#include "DirectionLeft.h"

DirectionLeft::DirectionLeft(){}

DirectionLeft::~DirectionLeft(){}

dir_ptr DirectionLeft::opposite(){
	return dir_ptr(new DirectionRight());
}

void DirectionLeft::move(Position& pos, float speed){
	pos.moveHorizontal(speed * -1);
}

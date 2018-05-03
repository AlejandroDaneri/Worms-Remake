#include "DirectionUp.h"
#include "DirectionDown.h"

DirectionUp::DirectionUp(){}

DirectionUp::~DirectionUp(){}

dir_ptr DirectionUp::opposite(){
	return dir_ptr(new DirectionDown());
}

void DirectionUp::move(Position& pos, float speed){
	pos.moveVertical(speed);
}

#include "DirectionUp.h"
#include "DirectionDown.h"

DirectionDown::DirectionDown(){}

DirectionDown::~DirectionDown(){}

dir_ptr DirectionDown::opposite(){
	return dir_ptr(new DirectionUp());
}

void DirectionDown::move(Position& pos, float speed){
	pos.moveVertical(speed * -1);
}
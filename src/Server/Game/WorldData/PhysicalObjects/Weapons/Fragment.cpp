#include "Fragment.h"

Fragment::Fragment(World& world, GameParameters& params, int dam, int radius):
	Weapon(world, params, dam, radius){}
		
Fragment::~Fragment(){}

void Fragment::setShootPosition(b2Vec2 pos){
	this->shoot_position = pos;
}

b2Vec2 Fragment::getShootPosition(){
	return this->shoot_position;
}

void Fragment::shoot(int angle){
	Weapon::shoot(1, angle, -1, -1, -1);
}

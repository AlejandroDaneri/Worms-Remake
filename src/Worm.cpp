#include "Worm.h"
#include "DirectionRight.h"
#include "DirectionUp.h"

Worm::Worm(Position position, int life): position(position), life(life), dir(new DirectionRight()){}

Worm::~Worm(){}

void Worm::change_dir(){
	this->dir = this->dir->opposite();
}

void Worm::set_weapon(weapon_ptr weapon){
	this->weapon = std::move(weapon);
}

void Worm::move(){
	this->dir->move(this->position, WORM_SPEED);
}

void Worm::jump(){
	dir_ptr up(new DirectionUp());
	up->move(this->position, 0.5);
	this->dir->move(this->position, 1);
}

void Worm::roll_back(){
	dir_ptr up(new DirectionUp());
	up->move(this->position, 1.2);
	this->dir->opposite()->move(this->position, 0.2);
}

void Worm::shoot(int angle, int power, int time){
	this->weapon->shoot(this->position, this->dir, angle, power, time);
}

void Worm::shoot(const Position& pos){
	this->weapon->shoot(pos);
}

Position Worm::getPosition(){
	return this->position;
}

weapon_ptr Worm::getWeapon(){
	return std::move(this->weapon);
}

Worm::Worm(Worm&& other): 
	position(other.position), life(other.life), 
	weapon(std::move(other.weapon)), dir(std::move(other.dir)){}

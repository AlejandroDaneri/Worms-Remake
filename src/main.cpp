#include "Worm.h"
#include "Bazooka.h"
#include "AirAttack.h"

#include <iostream>


int main(int argc, char* argv[]){
	Position pos(2,2);

	Worm worm (pos, 124);
	worm.move();
	worm.change_dir();
	worm.move();
	worm.move();

	worm.jump();


	weapon_ptr weapon(new Bazooka());

	worm.set_weapon(std::move(weapon));

	weapon_ptr w2(new AirAttack());

	worm.set_weapon(std::move(w2));


	return 0;
}
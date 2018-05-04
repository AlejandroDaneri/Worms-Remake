#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "WormsList.h"
#include "Weapon.h"

class Player{
	private:
		WormsList worms;

	public:
		Player(std::vector<Worm>&& worms);

		~Player();

		Worm& getCurrentWorm();

		void begin_turn();

};

#endif
#ifndef __SERVERTURN_H__
#define __SERVERTURN_H__

#include "server_Player.h"
#include <vector>

class Turn{
	private:
		std::vector<Player> players;
		size_t current;

	public:
		Turn();
		~Turn();

		void addPlayer(Player&& player);

		size_t get_players_size();

		Player& getCurrentPlayer();

		void begin_turn();

};

#endif

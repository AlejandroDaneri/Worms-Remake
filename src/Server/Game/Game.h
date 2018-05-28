#ifndef __GAME_H__
#define __GAME_H__

#include "Turn.h"
#include "GameParameters.h"
#include "Thread.h"
#include "Player.h"
#include "Worm.h"
#include <vector>
#include <memory>
#include "World.h"
#include "DataSender.h"

class Player;

class Game: public Thread{
	private:
		size_t players;
		GameParameters parameters;
		World world;
		Turn turn;
		std::unique_ptr<DataSender> data_sender;
		bool player_turn_active;

		void configure();
		void wait_to_world();

	public:
		Game(size_t players, const std::string& config_file, const std::string& map);
		~Game();

		void addPlayer(Player&& player);

		bool isFull();

		bool playerCanJoin(const std::string& player_name);

		void run() override;

		Worm& getCurrentWorm();

		void weaponChanged(const std::string& weapon);

		void updateScope(int angle);

		void endTurn();
};

#endif

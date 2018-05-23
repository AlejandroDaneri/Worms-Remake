#ifndef __GAME_H__
#define __GAME_H__

#include "Turn.h"
#include "GameParameters.h"
#include "Thread.h"
#include "Player.h"
#include "Worm.h"
#include <mutex>
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
		std::mutex mutex;
		std::unique_ptr<DataSender> data_sender;
		bool player_turn_active;

		void configure();
		void wait_to_world();

	public:
		Game(size_t players, const std::string& config_file, const std::string& config_editor);
		~Game();

		bool addPlayer(Player&& player);

		bool isFull();

		void run() override;

		Worm& getCurrentWorm();

		void endTurn();
};

#endif

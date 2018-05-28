#ifndef __GAMESLIST_H__
#define __GAMESLIST_H__

#include "Game.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <mutex>

typedef std::vector<std::string> games_list_t;

class GamesList{
	private:
		std::unordered_map<std::string, std::unique_ptr<Game>> games;
		std::mutex mutex;

	public:
		GamesList();

		~GamesList();

		void addGame(const std::string& game_name, const std::string& map, int max_players, Player&& player);

		games_list_t getJoinableGames(const std::string& player_name);

		void addPlayer(const std::string& game_name, Player&& player);

		void checkGames();
};

#endif

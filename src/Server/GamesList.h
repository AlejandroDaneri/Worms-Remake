#ifndef __GAMESLIST_H__
#define __GAMESLIST_H__

#include "Game.h"
#include <vector>
#include <string>

typedef std::vector<std::string> games_list_t;

class GamesList{
	private:
		

	public:
		

		bool addGame(const std::string& game_name, const std::string& map, int max_players, const std::string& player_name){return true;}///////////////////////////

		games_list_t getJoinableGames(const std::string& player_name){ return games_list_t();}

		bool addPlayer(const std::string& game_name, const std::string& player_name){return true;}

		void checkGames(){}


};

#endif

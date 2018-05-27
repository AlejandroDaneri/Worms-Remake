#include "GamesList.h"
#include "Path.h"

GamesList::GamesList(){}

GamesList::~GamesList(){}

bool GamesList::addGame(const std::string& game_name, const std::string& map, int max_players, Player& player){
	std::lock_guard<std::mutex> lock(this->mutex);
	auto it = this->games.find(game_name);
	if (it != this->games.end()){
		return false;
	}

	std::unique_ptr<Game> game(new Game(max_players, SERVER_CONFIG_FILE, map));
	this->games[game_name] = std::move(game);
	return this->games[game_name]->addPlayer(std::move(player));
}

games_list_t GamesList::getJoinableGames(const std::string& player_name){
	std::lock_guard<std::mutex> lock(this->mutex);
	games_list_t joinables;

	for (auto it = this->games.begin(); it != this->games.end(); ++it){
		if (it->second->playerCanJoin(player_name)){
			joinables.push_back(it->first);
		}
	}
	return std::move(joinables);
}

bool GamesList::addPlayer(const std::string& game_name, Player& player){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->games[game_name]->addPlayer(std::move(player));
}

void GamesList::checkGames(){
	std::lock_guard<std::mutex> lock(this->mutex);
	auto it = this->games.begin();
	while (it != this->games.end()){
		if (! it->second->isRunning()){
			it->second->join();
			it = this->games.erase(it); 
		} else {
			++it;
		}
	}
}
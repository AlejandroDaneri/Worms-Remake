#include "GamesList.h"
#include "Path.h"

GamesList::GamesList(){}

GamesList::~GamesList(){
	for (auto it = this->games.begin(); it != this->games.end(); ++it){
		it->second->join();
	}
}

void GamesList::addGame(const std::string& game_name, const std::string& map, int max_players, Player&& player){
	std::lock_guard<std::mutex> lock(this->mutex);
	auto it = this->games.find(game_name);
	if (it != this->games.end()){
        player.getProtocol().sendChar(false);
		return;
	}

	std::unique_ptr<Game> game(new Game(max_players, SERVER_CONFIG_FILE, MAPS_PATH + map));
	this->games[game_name] = std::move(game);
	this->games[game_name]->addPlayer(std::move(player));


	if (this->games[game_name]->isFull()){
		this->games[game_name]->start();
	}//////////////////////////////////////////////por ahora, mientras se permita un player
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

void GamesList::addPlayer(const std::string& game_name, Player&& player){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->games[game_name]->addPlayer(std::move(player));
	if (this->games[game_name]->isFull()){
		this->games[game_name]->start();
	}
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
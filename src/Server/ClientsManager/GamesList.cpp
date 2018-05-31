#include "GamesList.h"
#include "Path.h"
#include <iostream>

GamesList::GamesList(){}

GamesList::~GamesList(){
	for (auto it = this->games.begin(); it != this->games.end(); ++it){
		it->second->join();
		std::cout << "[INFO] Partida terminada: " << it->first << std::endl;
	}
}

bool GamesList::addGame(const std::string& game_name, const std::string& map, int max_players, Player& player){
	std::lock_guard<std::mutex> lock(this->mutex);
	auto it = this->games.find(game_name);
	if (it != this->games.end()){
		return false;
	}

	try{
		std::unique_ptr<Game> game(new Game(max_players, SERVER_CONFIG_FILE, MAPS_PATH + map));
		this->games[game_name] = std::move(game);
		std::cout << "[INFO] Nueva partida creada: " << game_name << std::endl;
	} catch (const std::exception& e){
		std::cout << "[ERROR] Error al crear partida: " << game_name << "-> " << e.what() << std::endl;
		return false;
	}

	bool result = this->games[game_name]->addPlayer(player);
	if (result){
		std::cout << "[INFO] Se unio un jugador a la partida: " << game_name << std::endl;
	}

	if (this->games[game_name]->isFull()){
		this->games[game_name]->start();
	}//////////////////////////////////////////////por ahora, mientras se permita un player

	return result;
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
	bool result = this->games[game_name]->addPlayer(player);
	if (result){
		std::cout << "[INFO] Se unio un jugador a la partida: " << game_name << std::endl;
	}
	if (this->games[game_name]->isFull()){
		std::cout << "[INFO] Partida iniciada: " << game_name << std::endl;
		this->games[game_name]->start();
	}
	return result;
}

void GamesList::checkGames(){
	std::lock_guard<std::mutex> lock(this->mutex);
	auto it = this->games.begin();
	while (it != this->games.end()){
		if (! it->second->isRunning()){
			std::cout << "[INFO] Partida terminada: " << it->first << std::endl;
			it->second->join();
			it = this->games.erase(it); 
		} else {
			++it;
		}
	}
}

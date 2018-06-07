#include "ClientHandler.h"
#include "MapsList.h"
#include <iostream>

ClientHandler::ClientHandler(Socket&& client, GamesList& games, std::mutex& mutex_cout):
	client(std::move(ServerProtocol(std::move(client)))), games(games),
	connected(false), mutex_cout(mutex_cout){}

ClientHandler::~ClientHandler(){}

void ClientHandler::run(){
	try{
		while(!this->connected){
			char action = this->client.getProtocol().receiveChar();
			std::string player_name = this->client.getProtocol().receiveString();
			this->client.setName(player_name);
			if (action == CREATE_GAME_ACTION){
				this->createGame();
			} else if (action == JOIN_GAME_ACTION){
				this->joinGame();
			}
		}
		
	} catch(const std::exception& e){
		std::lock_guard<std::mutex> lock(this->mutex_cout);
		std::cout << "[ERROR] Error con un cliente: " << e.what() << std::endl;
	}
	this->running = false;
}

void ClientHandler::stop(){
	this->client.getProtocol().stop();
}

void ClientHandler::createGame(){
	maps_list_t maps_list = MapsList::getAllMaps();

	size_t size = maps_list.size();
    this->client.getProtocol().sendLength(size);

	for (size_t i = 0; i < size; i++){
		this->client.getProtocol().sendString(maps_list[i]);
	}

	if (size == 0){
		return;
	}

	std::string map = this->client.getProtocol().receiveString();
	if (map.empty()){
		return;
	}
	std::string game_name = this->client.getProtocol().receiveString();
	int max_players = this->client.getProtocol().receiveLength();

	bool result = this->games.addGame(game_name, map, max_players, this->client);
	if (!result){
		this->client.getProtocol().sendChar(false);
	} else {
		this->connected = true;
	}

}

void ClientHandler::joinGame(){
	games_list_t games_list = this->games.getJoinableGames(this->client.getName());

	size_t size = games_list.size();
    this->client.getProtocol().sendLength(size);

	for (size_t i = 0; i < size; i++){
		this->client.getProtocol().sendString(games_list[i]);
	}

	if (size == 0){
		return;
	}

	std::string game_name = this->client.getProtocol().receiveString();
	if (game_name.empty()){
		return;
	}

	bool result = this->games.addPlayer(game_name, this->client);

	if (!result){
		this->client.getProtocol().sendChar(false);
	} else {
		this->connected = true;
	}
}

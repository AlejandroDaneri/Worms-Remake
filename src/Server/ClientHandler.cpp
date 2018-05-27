#include "ClientHandler.h"
#include "MapsList.h"

ClientHandler::ClientHandler(Socket&& client, GamesList& games):
	client(std::move(client)), games(games){}

ClientHandler::~ClientHandler(){}

void ClientHandler::run(){
	try{
		char action = this->client.receive_char();
		std::string player_name = this->client.receive_string();
		if (action == CREATE_GAME_ACTION){
			this->createGame(player_name);
		} else if (action == JOIN_GAME_ACTION){
			this->joinGame(player_name);
		}
		
	} catch(const std::exception& e){
		//Ocurrio un error con la conexion del cliente
		//No corta la ejecucion del servidor
	}
	this->running = false;
}

void ClientHandler::stop(){
	this->client.stop();
}

void ClientHandler::createGame(const std::string& player_name){
	maps_list_t maps_list = MapsList::getAllMaps();

	size_t size = maps_list.size();
	this->client.send_length(size);

	for (size_t i = 0; i < size; i++){
		this->client.send_string(maps_list[i]);
	}

	std::string map = this->client.receive_string();
	std::string game_name = this->client.receive_string();
	int max_players = this->client.receive_length();

	Player player(std::move(this->client), player_name);

	bool result = this->games.addGame(game_name, map, max_players, player);

	if (!result){
		player.getProtocol().send_char(result);
	}

}

void ClientHandler::joinGame(const std::string& player_name){
	games_list_t games_list = this->games.getJoinableGames(player_name);

	size_t size = games_list.size();
	this->client.send_length(size);

	for (size_t i = 0; i < size; i++){
		this->client.send_string(games_list[i]);
	}

	std::string game_name = this->client.receive_string();

	Player player(std::move(this->client), player_name);

	bool result = this->games.addPlayer(game_name, player);

	if (!result){
		player.getProtocol().send_char(result);
	}
}

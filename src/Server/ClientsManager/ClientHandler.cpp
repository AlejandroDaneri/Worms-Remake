#include "ClientHandler.h"
#include "MapsList.h"

ClientHandler::ClientHandler(Socket&& client, GamesList& games):
	client(std::move(client)), games(games){}

ClientHandler::~ClientHandler(){}

void ClientHandler::run(){
	try{
		char action = this->client.receiveChar();
		std::string player_name = this->client.receiveString();
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
    this->client.sendLength(size);

	for (size_t i = 0; i < size; i++){
		this->client.sendString(maps_list[i]);
	}

	std::string map = this->client.receiveString();
	std::string game_name = this->client.receiveString();
	int max_players = this->client.receiveLength();

	Player player(std::move(this->client), player_name);

	this->games.addGame(game_name, map, max_players, std::move(player));

}

void ClientHandler::joinGame(const std::string& player_name){
	games_list_t games_list = this->games.getJoinableGames(player_name);

	size_t size = games_list.size();
    this->client.sendLength(size);

	for (size_t i = 0; i < size; i++){
		this->client.sendString(games_list[i]);
	}

	std::string game_name = this->client.receiveString();

	Player player(std::move(this->client), player_name);

	this->games.addPlayer(game_name, std::move(player));
}

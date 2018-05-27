#include "ClientHandler.h"

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

}

void ClientHandler::joinGame(const std::string& player_name){
	
}

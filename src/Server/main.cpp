#include "Game.h"
#include "Socket.h"
#include "Path.h"
#include <iostream>

#define EXIT_CHAR 'q'

int main(int argc, char* argv[]){

	Socket socket(Socket::Server("7777", 10));

	Socket client = socket.accept_client();
	Player player(std::move(client), "Pepe");

	//Socket client2 = socket.accept_client();
	//Player player2(std::move(client2));

	Game game(1, CONFIG_PATH + "server_config.yaml", CONFIG_PATH + "config_editor_rotated.yaml");

	try{

		game.addPlayer(std::move(player));
		//game.addPlayer(std::move(player2));
		game.start();
		while (std::cin.get() != EXIT_CHAR){}
	}catch (const std::exception& e){}

	try{
		game.stop();
	}catch (const std::exception& e){}

	game.join();

	return 0;
}

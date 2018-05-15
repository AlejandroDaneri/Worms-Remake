#include "Game.h"
#include "Socket.h"
#include <iostream>

int main(int argc, char* argv[]){

	Socket socket(Socket::Server("7777", 10));

	Socket client = socket.accept_client();
	Player player(std::move(client));

	//Socket client2 = socket.accept_client();
	//Player player2(std::move(client2));

	Game game("./config/server_config.yaml", "./config/config_editor.yaml");

	try{

		game.addPlayer(std::move(player));
		//game.addPlayer(std::move(player2));
		game.start();
		while (std::cin.get() != 'q'){}
			std::cout << "recibio q" << std::endl;
	}catch (const std::exception& e){}

	try{
		game.stop();
	}catch (const std::exception& e){}

	game.join();

	return 0;
}
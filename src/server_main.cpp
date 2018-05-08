#include "Game.h"
#include "Socket.h"
#include <iostream>

int main(int argc, char* argv[]){

	Socket socket(Socket::Server("7777", 10));

	Socket client = socket.accept_client();
	Player player(std::move(client));

	Game game("config");

	try{

		game.addPlayer(std::move(player));
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
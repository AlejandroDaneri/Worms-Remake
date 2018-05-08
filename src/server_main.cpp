#include "Game.h"
#include "Socket.h"

int main(int argc, char* argv[]){

	Socket socket(Socket::Server("7777", 10));

	Socket client = socket.accept_client();
	Player player(std::move(client));

	Game game("config");

	game.addPlayer(std::move(player));
	game.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(100000));
	game.stop();
	game.join();

	return 0;
}
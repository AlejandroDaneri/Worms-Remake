#ifndef __CLIENTHANDLER_H__
#define __CLIENTHANDLER_H__

#include "Socket.h"
#include "Server.h"
#include "Thread.h"
#include "ServerProtocol.h"
#include "GamesList.h"

class ClientHandler: public Thread{
	private:
		ServerProtocol client;
		GamesList& games;

		void createGame(const std::string& player_name);
		void joinGame(const std::string& player_name);

	public:
		ClientHandler(Socket&& client, GamesList& games);
		~ClientHandler();

		//Ejecuta el client handler
		void run();

		//Se desconecta abruptamente del cliente
		void stop();
};

#endif

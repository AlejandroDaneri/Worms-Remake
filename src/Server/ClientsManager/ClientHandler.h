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

		/* Crea una partida nueva */
		void createGame(const std::string& player_name);

		/* Agrega un jugador a una partida */
		void joinGame(const std::string& player_name);

	public:
		/* Constructor */
		ClientHandler(Socket&& client, GamesList& games);

		/* Destructor */
		~ClientHandler();

		/* Ejecuta el client handler */
		void run();

		/* Se desconecta abruptamente del cliente */
		void stop();
};

#endif

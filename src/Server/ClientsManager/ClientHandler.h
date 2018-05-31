#ifndef __CLIENTHANDLER_H__
#define __CLIENTHANDLER_H__

#include "Socket.h"
#include "Server.h"
#include "Thread.h"
#include "Player.h"
#include "GamesList.h"

class ClientHandler: public Thread{
	private:
		Player client;
		GamesList& games;
		bool connected;

		/* Crea una partida nueva */
		void createGame();

		/* Agrega un jugador a una partida */
		void joinGame();

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

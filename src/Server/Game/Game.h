#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <memory>
#include "Turn.h"
#include "GameParameters.h"
#include "Thread.h"
#include "Player.h"
#include "Worm.h"
#include "World.h"
#include "DataSender.h"

class Player;

class Game: public Thread{
	private:
		size_t players;
		GameParameters parameters;
		World world;
		Turn turn;
		std::unique_ptr<DataSender> data_sender;
		bool player_turn_active;

		/* Realiza la configuracion inicial de la partida */
		void configure();

		/* Espera a que los objetos dejen de moverse */
		void wait_to_world();

	public:
        /* Constructor */
		Game(size_t players, const std::string& config_file, const std::string& map);

		/* Destructor */
		~Game();

		/* Agrega un jugador a la partida */
		void addPlayer(Player&& player);

		/* Devuelve true si la partida esta llena */
		bool isFull();

		/* Devuelve true si el jugador puede unirse a la partida */
		bool playerCanJoin(const std::string& player_name);

		/* Comienza la partida */
		void run() override;

		/* Devuelve el worm actual */
		Worm& getCurrentWorm();

		/* Finaliza el turno */
		void endTurn();
};

#endif

#ifndef __SERVERTURN_H__
#define __SERVERTURN_H__

#include "Player.h"
#include "PlayerDataReceiver.h"
#include "DataSender.h"
#include <vector>
#include <string>
#include <memory>

class Turn{
	private:
		std::vector<Player> players;
		std::vector<std::unique_ptr<PlayerDataReceiver>> receivers;
		std::string winner;
		size_t current;

		void advanceCurrent();

	public:
		Turn();
		~Turn();

		//Agrega un nuevo jugador
		bool addPlayer(Player& player);

		//Devuelve true si el jugador se puede unir a la partida
		bool playerCanJoin(const std::string& player_name);

		//Devuelve la cantidad de jugadores
		size_t getPlayersSize() const;

		//Devuelve un vector con los jugadores
		std::vector<Player>& getPlayers();

		//Devuelve el jugador actual
		Player& getCurrentPlayer();

		//Realiza la configuracion inicial
		void startGame(DataSender& data_sender);

		//Empieza un nuevo turno, cambiando el jugador actual
		void beginTurn();

		//Termina el turno del jugador actual
		void endTurn();

		//Agrega un gusano al proximo jugador
		void addWorm(World& world, GameParameters& parameters, b2Vec2 position, int id);

		//Agrega vida a los jugadores con menos gusanos
		void distributeWorms(size_t size, int life_to_add);

		//Devuelve true si queda uno o ningun jugador vivo
		bool gameEnded(std::mutex& mutex);

		//Devuelve el nombre del jugador ganador
		const std::string& getWinner();

};

#endif

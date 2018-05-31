#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "WormsList.h"
#include "ServerProtocol.h"
#include "Worm.h"
#include "World.h"
#include "GameParameters.h"
#include <string>

class Player{
	private:
		ServerProtocol protocol;
		std::string name;
		WormsList worms;
		int id;
		bool connected;

	public:
		Player(ServerProtocol&& protocol);

		Player(Player&& other);

		~Player();

		void setId(int id);

		int getId() const;

		//Devuelve el gusano actual del jugador
		Worm& getCurrentWorm();

		//Empieza el turno del jugador
		void begin_turn();

		//Agrega un nuevo gusano al jugador
		void addWorm(World& world, GameParameters& parameters, const b2Vec2& position, int id);

		//Agrega vida a los gusanos del jugador 
		//en caso de que tenga menos gusanos que otros jugadores
		void distributeWorms(size_t max, int life_to_add);

		//Devuelve true si el jugador esta muerto
		bool isDead();

		//Devuelve true si el jugador esta desconectado
		bool isConnected() const;

		//Desconecta al jugador
		void disconnect();

		void setName(const std::string& name);

		const std::string& getName() const;

		ServerProtocol& getProtocol();

};

#endif

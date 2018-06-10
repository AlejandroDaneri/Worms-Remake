#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "WormsList.h"
#include "ServerProtocol.h"
#include "Worm.h"
#include "World.h"
#include "GameParameters.h"
#include "WeaponList.h"
#include <string>

class Player{
	private:
		ServerProtocol protocol;
		std::string name;
		WormsList worms;
		WeaponList weapons;
		int id;
		bool connected;

	public:
		Player(ServerProtocol&& protocol);

		Player(Player&& other);

		~Player();

		//Setea el id del jugador por el pasado
		void setId(int id);

		//Devuelve el id del jugador
		int getId() const;

		//Devuelve el gusano actual del jugador
		Worm& getCurrentWorm();

		//Empieza el turno del jugador
		void beginTurn();

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

		//Setea la municion de las armas
		void setWeaponsAmmo(const std::map<std::string, unsigned int>& ammo);

		//Cambia el arma actual del jugador
		void changeWeapon(const std::string& weapon);

		//Setea el nombre del jugador
		void setName(const std::string& name);

		//Devuelve el nombre del jugador
		const std::string& getName() const;

		//Devuelve el protocolo del jugador
		ServerProtocol& getProtocol();

};

#endif

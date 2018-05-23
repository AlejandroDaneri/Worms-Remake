#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "WormsList.h"
#include "Socket.h"
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
		Player(Socket&& socket, const std::string& name);

		Player(Player&& other);

		~Player();

		void setId(int id);

		int getId() const;

		Worm& getCurrentWorm();

		void begin_turn();

		void addWorm(World& world, GameParameters& parameters, const b2Vec2& position, int id);

		void distributeWorms(size_t max, int life_to_add);

		bool isDead();

		bool isConnected() const;

		void disconnect();

		const std::string& getName() const;

		ServerProtocol& getProtocol();

};

#endif

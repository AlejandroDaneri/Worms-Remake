#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "WormsList.h"
#include "Socket.h"
#include "server_Protocol.h"
#include "Worm.h"
#include "World.h"
#include "GameParameters.h"

class Player{
	private:
		ServerProtocol protocol;
		WormsList worms;
		int id;

	public:
		Player(Socket&& socket);

		Player(Player&& other);

		~Player();

		void setId(int id);

		Worm& getCurrentWorm();

		void begin_turn();

		void addWorm(World& world, GameParameters& parameters, const b2Vec2& position, int id);

		void distributeWorms(size_t max, int life_to_add);

		bool isDead();

		ServerProtocol& getProtocol();

};

#endif

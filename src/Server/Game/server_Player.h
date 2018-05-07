#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "WormsList.h"
#include "Socket.h"
#include "server_Protocol.h"
#include "Worm.h"
#include "World.h"

class Player{
	private:
		Protocol protocol;
		WormsList worms;

	public:
		Player(Socket&& socket);

		Player(Player&& other);

		~Player();

		worm_ptr getCurrentWorm();

		void begin_turn();

		void add_worm(World& world, int id, const b2Vec2& position);

};

#endif
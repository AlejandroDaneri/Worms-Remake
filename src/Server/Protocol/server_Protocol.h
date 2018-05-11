#ifndef __SERVERPROTOCOL_H__
#define __SERVERPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "PhysicalObject.h"
#include <mutex>

class Game;

class ServerProtocol : public Protocol{
	private:

		void send_worm(physical_object_ptr& object, char* buffer);
		void send_weapon(physical_object_ptr& weapon, char* buffer);

	public:
		ServerProtocol(Socket&& socket);
		ServerProtocol(ServerProtocol&& other);
		~ServerProtocol();

		void sendObject(physical_object_ptr& object);

		void sendDeadObject(physical_object_ptr& object);

		void receive(Game& game);

		void send_start_turn(uint32_t current_worm_id);
};

#endif

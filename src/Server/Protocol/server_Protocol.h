#ifndef __SERVERPROTOCOL_H__
#define __SERVERPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "PhysicalObject.h"
#include <mutex>

class Game;

class Protocol{
	private:
		Socket socket;
		std::mutex mutex_send;

		void send_worm(physical_object_ptr& object, char* buffer);
		void send_weapon(physical_object_ptr& weapon, char* buffer);
		void send_string(const char* buffer, size_t size);

	public:
		Protocol(Socket&& socket);
		Protocol(Protocol&& other);
		~Protocol();

		void sendObject(physical_object_ptr& object);

		void sendDeadObject(physical_object_ptr& object);

		void receive(Game& game);

		void send_start_turn(uint32_t current_worm_id);

		void stop();

};

#endif

#ifndef __SERVERPROTOCOL_H__
#define __SERVERPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "Game.h"
#include "PhysicalObject.h"
#include <mutex>

class Protocol{
	private:
		Socket socket;
		std::mutex mutex_send;

	public:
		Protocol(Socket&& socket);
		~Protocol();

		void sendObject(physical_object_ptr& object);

		void sendDeadObject(physical_object_ptr& object);

		void receive(Game& game);

};

#endif

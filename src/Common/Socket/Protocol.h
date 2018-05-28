#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include <mutex>
#include "Buffer.h"
#include "Socket.h"

#define MAX_STRING_SIZE 200

#define CREATE_GAME_ACTION 0
#define JOIN_GAME_ACTION 1
#define START_GAME_ACTION 1

#define MOVING_OBJECT 0
#define DEAD_OBJECT 1
#define ACTION 2


#define START_TURN 3
#define END_TURN 4
#define MOVE_ACTION 5
#define CHANGE_WEAPON_ACTION 6
#define SHOOT_WEAPON 7
#define SHOOT_SELF_DIRECTED 8
#define MOVE_SCOPE 9


#define MOVE_RIGHT 1
#define MOVE_LEFT -1
#define JUMP 2
#define ROLLBACK 3

#define WORM_TYPE 0
#define WEAPON_TYPE 1
#define GIRDER_TYPE 2

class Protocol {
	private:
		Socket socket;
		std::mutex mutex_send;
	public:
		Protocol(Socket&& socket);
		Protocol(Protocol&& other);
		~Protocol();
		
		void sendBuffer(Buffer &buffer);
		Buffer receiveBuffer();
		
		void sendIntBuffer(Buffer &buffer, int32_t value);
		int receiveIntBuffer(Buffer &buffer);
		
		void sendStringBuffer(Buffer &buffer, const std::string &string);
		std::string receiveStringBuffer(Buffer &buffer);

		void sendLength(uint32_t length);
		size_t receiveLength();
		
		void stop();

		//Envia un char
		void sendChar(unsigned char c);

		//Recibe un char
		unsigned char receiveChar();

		//Envia un string
		void sendString(const std::string &string);

		//Recibe un string
		std::string receiveString();
};

#endif

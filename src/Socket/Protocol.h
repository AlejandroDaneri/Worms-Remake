#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include <mutex>
#include "Socket.h"

#define MAX_BUF_LEN 1024

#define MOVING_OBJECT 0
#define DEAD_OBJECT 1
#define ACTION 2


#define START_TURN 3
#define END_TURN 4
#define MOVE_ACTION 5
#define CHANGE_WEAPON_ACTION 6
#define SHOOT_WEAPON 7
#define SHOOT_SELF_DIRECTED 8

#define MOVE_RIGHT 1
#define MOVE_LEFT -1
#define JUMP 2
#define ROLLBACK 3
#define EXTEND_ANGLE 4/////////////////////////
#define REDUCE_ANGLE 5/////////////////////////

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
		
		void send_buffer(const char* buffer, size_t size);
		size_t receive_buffer(char* buffer);
		
		void send_int(char* buffer, size_t& offset, int32_t value);
		int receive_int(char* buffer, size_t& offset);
		
		void send_string(char* buffer, size_t& offset, const std::string& string);
		std::string receive_string(char* buffer, size_t& offset); 

		void send_length(uint32_t length);
		
		void stop();
};

#endif

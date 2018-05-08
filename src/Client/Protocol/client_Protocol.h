#ifndef __CLIENTPROTOCOL_H__
#define __CLIENTPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "Position.h"
#include "client_Player.h"
#include "ViewsList.h"

class Protocol{
	private:
		Socket socket;

		void send_string(const char* buffer, size_t size);

	public:
		Protocol(Socket&& socket);
		Protocol(Protocol&& other);
		~Protocol();

		void send_move_action(char action);

		void send_change_weapon(const std::string& weapon);

		void send_weapon_shoot(uint32_t angle, uint32_t power, uint32_t time);

		void send_weapon_self_directed_shoot(const Position& pos);

		void send_end_turn();

		void receive(Player& player, ViewsList& viewsList);

		void stop();
};

#endif

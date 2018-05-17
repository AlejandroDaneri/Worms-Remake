#ifndef __CLIENTPROTOCOL_H__
#define __CLIENTPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "Position.h"
#include "ViewsList.h"

class Player;
class WeaponList;

class ClientProtocol: public Protocol {
	public:
		ClientProtocol(Socket&& socket);
		ClientProtocol(ClientProtocol&& other);
		~ClientProtocol();

		void send_move_action(char action);

		void send_change_weapon(const std::string& weapon);

		void send_weapon_shoot(int32_t angle, int32_t power, int32_t time);

		void send_weapon_self_directed_shoot(const Position& pos);

		void send_end_turn();

		void receive(Player& player, ViewsList& viewsList);

		void receivePlayers(); ///////////////////////////////////////////////ver parametros que recibe

		void receiveGirders(ViewsList& viewsList);

		void receiveWeaponsAmmo(WeaponList& weapon_list);
};

#endif

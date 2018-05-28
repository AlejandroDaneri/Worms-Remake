#ifndef __SERVERPROTOCOL_H__
#define __SERVERPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "PhysicalObject.h"
#include <mutex>

class Game;
class Player;
class DataSender;

class ServerProtocol : public Protocol{
	private:

		void send_worm(physical_object_ptr& object, Buffer& buffer);
		void send_weapon(physical_object_ptr& weapon, Buffer& buffer);

	public:
		ServerProtocol(Socket&& socket);
		ServerProtocol(ServerProtocol&& other);
		~ServerProtocol();

		Buffer sendObject(physical_object_ptr& object);

		Buffer sendDeadObject(physical_object_ptr& object);

		void receive(Game& game, DataSender& data_sender);

		void send_start_turn(int32_t current_worm_id, int32_t current_player_id);

		void sendPlayerId(const Player& player);

		void sendGirder(physical_object_ptr& girder);

		void sendWeaponAmmo(const std::string& weapon_name, int ammo);

		void send_weapon_changed(const std::string& weapon);

		void sendUpdateScope(int angle);
};

#endif

#ifndef __DATASENDER_H__
#define __DATASENDER_H__

#include "Thread.h"
#include "World.h"
#include "PhysicalObject.h"
#include "Player.h"
#include "ServerProtocol.h"
#include "PlayerDataSender.h"
#include <list>
#include <memory>

class DataSender: public Thread{
	private:
		std::list<physical_object_ptr>& objects;
		std::list<physical_object_ptr>& girders;
		std::vector<Player>& players;
		std::vector<std::unique_ptr<PlayerDataSender>> players_data_senders;
		std::mutex& mutex;
		bool active;

		void sendBuffer(const Buffer& buffer);
		void notifyAll();

	public:
		DataSender(World& world, std::vector<Player>& players);
		~DataSender();

		void run() override;

		void send_players_id();
		void sendGirders();
		void sendWeaponsAmmo(std::map<std::string, int>& weapons);
		void send_weapon_changed(const std::string& weapon);
		void sendUpdateScope(int angle);

		void send_start_game();
		void send_start_turn(int worm_id, int player_id);
		void sendEndGame(const std::string& winner);

		bool isActive();

};


#endif

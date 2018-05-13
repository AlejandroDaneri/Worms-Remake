#ifndef __DATASENDER_H__
#define __DATASENDER_H__

#include "Thread.h"
#include "World.h"
#include "PhysicalObject.h"
#include "server_Player.h"
#include "server_Protocol.h"
#include <list>

class DataSender: public Thread{
	private:
		std::list<physical_object_ptr>& objects;
		std::list<physical_object_ptr>& girders;
		std::vector<Player>& players;
		std::mutex& mutex;

	public:
		DataSender(World& world, std::vector<Player>& players);
		~DataSender();

		void run() override;

		void sendGirders();
		void sendWeaponsAmmo(std::map<std::string, int>& weapons);

};


#endif

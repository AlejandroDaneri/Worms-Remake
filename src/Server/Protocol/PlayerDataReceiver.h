#ifndef __PLAYERDATARECEIVER_H__
#define __PLAYERDATARECEIVER_H__

#include "Thread.h"
#include "Player.h"
#include "DataSender.h"
#include <mutex>

class PlayerDataReceiver: public Thread{
	private:
		Player& player;
		DataSender& data_sender;
		bool is_my_turn;
		std::mutex mutex;

		void analizeReceivedData(Buffer& data);

	public:
		PlayerDataReceiver(Player& player, DataSender& data_sender);

		~PlayerDataReceiver();

		void run() override;

		void beginTurn();

		void endTurn();

};

#endif

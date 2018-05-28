#ifndef __PLAYERDATASENDER_H__
#define __PLAYERDATASENDER_H__

#include "Thread.h"
#include "Player.h"
#include "Buffer.h"
#include <mutex>
#include <condition_variable>
#include <queue>

class PlayerDataSender: public Thread{
	private:
		std::mutex mutex;
		std::condition_variable condition_variable;
		Player& player;
		std::queue<Buffer> queue;

	public:
		PlayerDataSender(Player& player);

		~PlayerDataSender();

		void run() override;

		void sendData(Buffer buffer);

		void notify();

		void stop() override;

};

#endif

#ifndef __CLIENTTURN_H__
#define __CLIENTTURN_H__

#include "Thread.h"
#include <unistd.h>

class Player;

class Turn : public Thread {
	private:
		bool running;
		int actual_time;
		int max_time;
		Player& player;

	public:
		Turn(Player& player);
		~Turn();
		Turn(Turn&& other);

		void run();
		void stopRun();
		void reduceTime(int timeReduction);
};

#endif

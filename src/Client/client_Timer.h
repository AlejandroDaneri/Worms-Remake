#ifndef __CLIENTTIMER_H__
#define __CLIENTTIMER_H__

#include "Thread.h"

class Player;

class Timer : public Thread {
	private:
		int32_t actual_time;
		int32_t max_time;
		Player& player;

	public:
		Timer(Player& player, int time);
		~Timer();

		void run();
};

#endif

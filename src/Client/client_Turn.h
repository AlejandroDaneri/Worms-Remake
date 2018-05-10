#ifndef __TURNO_H__
#define __TURNO_H__

#include "Thread.h"
#include <unistd.h>
#include "client_Player.h"

class Turno : Thread{
	private:
		bool running;
		int actual_time;
		int max_time;
		Player& player;

	public:
		Turno(int max_time, Player& player);
		~Turno();

		void run();
		void stopRun();
		void reduceTime(int timeReduction);
};

#endif

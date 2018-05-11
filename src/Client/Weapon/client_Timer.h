#ifndef __CLIENTTIMER_H__
#define __CLIENTTIMER_H__

#include "Thread.h"
#include <unistd.h>

class Timer : public Thread {
	private:
		bool running;
		int max_time;

	public:
		Timer(int time);
		~Timer();

		void run(); // recibe el arma
		void stopRun();
};

#endif

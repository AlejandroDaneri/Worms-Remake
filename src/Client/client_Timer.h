#ifndef __CLIENTTIMER_H__
#define __CLIENTTIMER_H__

#include "Thread.h"

class Handlers;

class Timer : public Thread {
	private:
		int actual_time;
		int max_time;
		Handlers& handlers;

	public:
		Timer(Handlers& handlers, int time);
		~Timer();

		void run();
};

#endif

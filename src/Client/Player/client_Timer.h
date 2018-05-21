#ifndef __CLIENTTIMER_H__
#define __CLIENTTIMER_H__

#include "Thread.h"

class Handlers;

/* Clase que simula a un contador */
class Timer : public Thread {
	private:
		int actual_time;
		int max_time;
		Handlers& handlers;

	public:
		/* Constructor */
		Timer(Handlers& handlers, int time);

		/* Destructor */
		~Timer();

		/* Cuenta el tiempo transcurrido y llama al metodo timerStopped
		   de la clase Handler con este tiempo */
		void run();
};

#endif

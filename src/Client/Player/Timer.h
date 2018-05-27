#ifndef __CLIENTTIMER_H__
#define __CLIENTTIMER_H__

#include <glibmm/main.h>

class Handlers;

/* Clase que simula a un contador */
class Timer {
	private:
		int actual_time;
		int max_time;
		Handlers& handlers;
        sigc::connection my_connection;

        /* Callback de start */
        bool startCallBack();

	public:
		/* Constructor */
		Timer(Handlers& handlers, int time);

		/* Destructor */
		~Timer();

		/* Cuenta el tiempo transcurrido y llama al metodo timerStopped
		   de la clase Handler con este tiempo */
		void start();

		/* Detiene el contador */
		void stop();
};

#endif

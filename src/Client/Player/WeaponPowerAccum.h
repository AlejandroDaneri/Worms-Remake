#ifndef __CLIENTTIMER_H__
#define __CLIENTTIMER_H__

#include <glibmm/main.h>

class Handlers;

/* Clase que simula a un contador */
class WeaponPowerAccum {
	private:
		int actual_time;
		int max_time;
		int power;
		Handlers& handlers;
		sigc::connection my_connection;

		/* Callback de start */
		bool startCallBack();

	public:
		/* Constructor */
		WeaponPowerAccum(Handlers& handlers, int time);

		/* Destructor */
		~WeaponPowerAccum();

		/* Cuenta el tiempo transcurrido y llama al metodo timerStopped
		   de la clase Handler con este tiempo */
		void start();

		/* Detiene el contador */
		void stop();
};

#endif

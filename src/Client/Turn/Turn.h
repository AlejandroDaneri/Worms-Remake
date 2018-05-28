#ifndef __CLIENTTURN_H__
#define __CLIENTTURN_H__

#include "TurnLabel.h"

class Player;

/* Clase que se encarga de contar el tiempo del turno */
class Turn {
	private:
		int actual_time;
		Player& player;
		TurnLabel& time_label;
		sigc::connection my_connection;

		/* Callback de start */
		bool startCallBack();

	public:
	    /* Constructor */
		Turn(Player& player, TurnLabel& time_label);

		/* Destructor */
		~Turn();


		/* Comienza la cuenta regresiva del turno actualizando el
		 * label que muestra el tiempo */
	    void start();

	    /* Reduce el tiempo restante del turno a 3 segundos */
		void reduceTime();

		/* Detiene el contador y finaliza el turno */
		void stop();
};

#endif

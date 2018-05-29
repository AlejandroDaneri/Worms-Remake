#ifndef __DATARECEIVER_H__
#define __DATARECEIVER_H__

#include "Thread.h"
#include "ClientProtocol.h"

class Player;

/* Clase que se encarga de recibir los mensajes enviados por el servidor */
class DataReceiver: public Thread{
	private:
		Player& player;
		ClientProtocol& protocol;

		void initialConfig();

	public:
		/* Constructor */
		DataReceiver(Player& player);

		/* Destructor */
		~DataReceiver();

		/* Comienza a recibir mensajes del protocolo */
		void run() override;

		/* Detiene el proceso de recibir mensajes */
		void stop() override;

};


#endif

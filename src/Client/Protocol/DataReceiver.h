#ifndef __DATARECEIVER_H__
#define __DATARECEIVER_H__

#include "Thread.h"
#include "ViewsList.h"
#include "ClientProtocol.h"

class Player;

/* Clase que se encarga de recibir los mensajes enviados por el servidor */
class DataReceiver: public Thread{
	private:
		ViewsList& views;
		Player& player;
		ClientProtocol& protocol;

	public:
		/* Constructor */
		DataReceiver(ViewsList& views, Player& player, ClientProtocol& protocol);

		/* Destructor */
		~DataReceiver();


		/* Comienza a recibir mensajes del protocolo */
		void run() override;

		/* Detiene el proceso de recibir mensajes */
		void stop() override;

};


#endif

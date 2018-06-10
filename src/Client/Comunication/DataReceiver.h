#ifndef __DATARECEIVER_H__
#define __DATARECEIVER_H__

#include "Thread.h"
#include "ClientProtocol.h"

class Player;

/* Clase que se encarga de recibir los mensajes
 * enviados por el servidor */
class DataReceiver : public Thread {
private:
	Player& player;
	ClientProtocol& protocol;

	/* Recibe los datos de la configuracion inicial */
	void initialConfig();

	/* Analiza los datos recibidos */
	bool analizeReceivedData(Buffer buffer);

public:
	/* Constructor */
	explicit DataReceiver(Player& player);

	/* Destructor */
	~DataReceiver();

	/* Comienza a recibir mensajes del protocolo */
	void run() override;
};


#endif

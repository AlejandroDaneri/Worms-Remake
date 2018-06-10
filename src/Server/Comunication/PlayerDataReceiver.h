#ifndef __PLAYERDATARECEIVER_H__
#define __PLAYERDATARECEIVER_H__

#include "Thread.h"
#include "Player.h"
#include "DataSender.h"
#include <mutex>

/* Clase que se encarga de recibir datos del jugador
 * y de analizarlos */
class PlayerDataReceiver: public Thread{
	private:
		Player& player;
		DataSender& data_sender;
		bool is_my_turn;
		std::mutex mutex;

		/* Analiza los datos recibidos */
		void analizeReceivedData(Buffer& data);

	public:
		/* Constructor */
		PlayerDataReceiver(Player& player, DataSender& data_sender);

		/* Destructor */
		~PlayerDataReceiver();

		/* Comienza a recibir datos */
		void run() override;

		/* Comienza el turno */
		void beginTurn();

		/* Termina el turno */
		void endTurn();
};

#endif

#ifndef __PLAYERDATASENDER_H__
#define __PLAYERDATASENDER_H__

#include "Thread.h"
#include "Player.h"
#include "Buffer.h"
#include <mutex>
#include <condition_variable>
#include <queue>

//Cola bloqueante para enviar datos a un jugador
class PlayerDataSender: public Thread{
	private:
		std::mutex mutex;
		std::condition_variable condition_variable;
		Player& player;
		std::queue<Buffer> queue;

	public:
		PlayerDataSender(Player& player);

		~PlayerDataSender();

		//Envia datos al jugador
		void run() override;

		//Agrega un nuevo dato a la cola
		void sendData(Buffer buffer);

		//Notifica que hay nuevos datos
		void notify();

		//Termina el envio de datos
		void stop() override;

};

#endif

#ifndef __DATASENDER_H__
#define __DATASENDER_H__

#include "Thread.h"
#include "World.h"
#include "PhysicalObject.h"
#include "Player.h"
#include "ServerProtocol.h"
#include "PlayerDataSender.h"
#include <list>
#include <memory>

class DataSender: public Thread{
	private:
		std::list<physical_object_ptr>& objects;
		std::list<physical_object_ptr>& girders;
		std::vector<Player>& players;
		std::vector<std::unique_ptr<PlayerDataSender>> players_data_senders;
		std::mutex& mutex;
		bool active;
		int sleep_time;

		void sendBuffer(const Buffer& buffer);
		void notifyAll();

	public:
		DataSender(World& world, std::vector<Player>& players, GameParameters& parameters);
		~DataSender();

		//Envia constantemente los datos de los objetos
		void run() override;

		//Envia la imagen de fondo
		void sendBackgroundImage(File& image);

		//Envia los datos del turno
		void sendTurnData(int turn_time, int time_after_shoot);

		//Envia los datos de los jugadores
		void sendPlayersId();

		//Envia los datos de las vigas
		void sendGirders();

		//Envia las municiones de las armas
		void sendWeaponsAmmo(std::map<std::string, unsigned int>& weapons);

		//Envia que el jugador cambio de arma
		void sendWeaponChanged(const std::string &weapon);

		//Envia que el gusano actual salto
		void sendMoveAction(char action);

		//Envia que el jugador cambio el angulo de la mira
		void sendUpdateScope(int angle);

		//Envia que el jugador disparo un arma
		void sendWeaponShot(const std::string& weapon);

		//Envia la senial de comienzo del juego
		void sendStartGame();

		//Envia la senial de que inicia un nuevo turno
		void sendStartTurn(int worm_id, int player_id, float wind);

		//Envia la senial de terminar turno
		void sendEndTurn();

		//Envia la senial de que el juego termino
		void sendEndGame(const std::string& winner);

		//Devuelve true si sigue enviando datos
		bool isActive();
};


#endif

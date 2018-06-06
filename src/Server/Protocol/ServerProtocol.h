#ifndef __SERVERPROTOCOL_H__
#define __SERVERPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "PhysicalObject.h"
#include <mutex>

class Game;
class Player;
class DataSender;

class ServerProtocol : public Protocol{
	private:
		//Carga los datos del gusano en el buffer
		static void send_worm(physical_object_ptr& object, Buffer& buffer);

		//Carga los datos del arma en el buffer
		static void send_weapon(physical_object_ptr& weapon, Buffer& buffer);

	public:
		ServerProtocol(Socket&& socket);
		ServerProtocol(ServerProtocol&& other);
		~ServerProtocol();

		//Carga un nuevo objeto en el buffer
		static Buffer sendObject(physical_object_ptr& object);

		//Carga la informacion de un objeto muerto en el buffer
		static Buffer sendDeadObject(physical_object_ptr& object);

		//Recibe datos de un cliente
		void receive(Game& game, DataSender& data_sender);

		//Carga la informacion de comienzo de juego
		static Buffer sendStartGame();

		//Carga la informacion de nuevo turno en el buffer
		static Buffer sendStartTurn(int32_t current_worm_id, int32_t current_player_id, float wind);

		//Carga la informacion de un nuevo jugador en el buffer
		static Buffer sendPlayerId(const Player& player);

		//Carga la informacion de una viga en el buffer
		static Buffer sendGirder(physical_object_ptr& girder);

		//Carga la informacion de un arma en el buffer
		static Buffer sendWeaponAmmo(const std::string& weapon_name, int ammo);

		//Carga la informacion de cambio de arma en el buffer
		static Buffer sendWeaponChanged(const std::string &weapon);

		//Carga la informacion de arma disparada en el buffer
		static Buffer sendWeaponShot(const std::string &weapon);

		//Carga la informacion de que el gusano salto
		static Buffer sendMoveAction(char action);

		//Carga la informacion de cambio de angulo en el buffer
		static Buffer sendUpdateScope(int angle);

		//Carga la informacion de fin del juego en el buffer
		static Buffer sendEndGame(const std::string& winner);

		//Carga la informacion de fin del turno
		static Buffer sendEndTurn();
};

#endif

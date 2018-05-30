#ifndef __CLIENTPROTOCOL_H__
#define __CLIENTPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "Position.h"
#include "ViewsList.h"
#include "PlayersList.h"

class Player;
class WeaponList;

/* Clase que se encarga de enviar y recibir mensajes del socket
 * con un formato determinado */
class ClientProtocol: public Protocol {
	public:
		/* Constructor */
		ClientProtocol(Socket&& socket);

		/* Constructor por movimiento */
		ClientProtocol(ClientProtocol&& other);

		/* Destructor */
		~ClientProtocol();

		/* Envia un mensaje que indica una accion de movimiento */
		void sendMoveAction(char action);

		/* Envia un mensaje que indica una accion de cambio de arma
		 * con el nombre del arma */
		void sendChangeWeapon(const std::string &weapon);

		/* Envia un mensaje de accion de disparo, con el angulo, la potencia
		 * y el tiempo de explosion */
		void sendWeaponShoot(int32_t angle, int32_t power, int32_t time);

		/* Envia un mensaje de accion de disparo teledirigido con
		 * la posicion del disparo */
		void sendWeaponSelfDirectedShoot(const Position &pos);

		/* Envia un mesaje que indica el cambio del angulo del scope */
		void updateScope(int angle);

		/* Envia un mensaje de finalizacion de turno */
		void sendEndTurn();

		/* Recibe un mensaje que le indica que accion realizar */
		void receive(Player& player);

		/* Recibe el comienzo del juego */
		void receiveStartGame();

		/* Recibe los jugadores de la partida junto con su
		 * id y su nombre */
		void receivePlayers(PlayersList& players_list);

		/* Recibe la vigas presentes en el mapa junto con su tamaño,
		 * su posicion y su rotacion */
		void receiveGirders(ViewsList& viewsList);

		/* Recibe las armas presentes en el juego junto con
		 * su municion */
		void receiveWeaponsAmmo(WeaponList& weapon_list);
};

#endif

#ifndef __CLIENTPLAYER_H__
#define __CLIENTPLAYER_H__

#include <memory>
#include "ClientProtocol.h"
#include "WorldView.h"
#include "Turn.h"
#include "Weapon.h"
#include "WeaponList.h"
#include "WorldView.h"
#include "WeaponView.h"
#include "ScreenView.h"
#include "ViewsList.h"
#include "Position.h"
#include "DataReceiver.h"
#include "Handlers.h"
#include "PlayersList.h"
#include "TurnLabel.h"

class Player {
	private:
		ClientProtocol protocol;
		std::string name;
		WeaponList weapons;
		TurnLabel turn_label;
		PlayersList players_list;
		ScreenView screen;
		std::unique_ptr<Turn> turn;
		ViewsList view_list;
		DataReceiver data_receiver;
		Handlers handlers;

		/* Reduce el tiempo del turno y actualiza la municion */
		void shootWeapon();

	public:
		/* Constructor */
		Player(ClientProtocol protocol, const std::string& name);
		
		/* Destructor */
		~Player();


		/* Comienza el turno. Si es el turno del jugador entonces,
		   habilita los handlers, sino muestra los movimientos realizados
		   por el otro jugador */
		void startTurn(int worm_id, int player_id);
		
		/* Finaliza el turno del jugador actual */
		void endTurn();

		/* El jugador actual recibio danio */
		void damageReceived();

		/* Cambia el arma actual por la espeificada */
		void change_weapon(std::string weapon);
		
		/* Realiza el disparo del arma con el angulo, potencia 
		   y tiempo pasados */
		void shoot(int angle, int power, int time);
		
		/* Realiza el disparo del arma en la posicion pasada */
		void shoot(Position position);
		
		/* Actualiza la vista del WeaponView */
		void update_weapons_view(std::string weapon);
		
		/* Reproduce el sonido de falta de tiempo */
		void play_tick_time();
		
		/* Devuelve la ventana donde se encuentra la vista completa */
		Gtk::Container& getWindow();
		
		/* Devuelve el contenedor del mapa */
		WorldView& getWorld();
		
		/* Devuelve la lista de los elementos presentes en la vista */
		ViewsList& getViewList();

		/* Devuelve el protocolo */
		ClientProtocol& getProtocol();
};

#endif

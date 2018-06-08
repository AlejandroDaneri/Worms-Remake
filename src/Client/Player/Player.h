#ifndef __CLIENTPLAYER_H__
#define __CLIENTPLAYER_H__

#include <memory>
#include <gtkmm/window.h>
#include "MenuView.h"
#include "ClientProtocol.h"
#include "Turn.h"
#include "Weapon.h"
#include "WeaponList.h"
#include "ScreenView.h"
#include "ViewsList.h"
#include "Position.h"
#include "DataReceiver.h"
#include "Handlers.h"
#include "MusicPlayer.h"

class Player {
	private:
		ClientProtocol& protocol;
		std::string name;
		WeaponList weapons;
		ScreenView screen;
		Turn turn;
		ViewsList view_list;
		DataReceiver data_receiver;
		Handlers handlers;
		MusicPlayer musicPlayer;

		/* Reduce el tiempo del turno y actualiza la municion */
		void shootWeapon();

	public:
		/* Constructor */
		Player(ClientProtocol& protocol, const std::string& name, Gtk::Window& window, MenuView& main_menu);
		
		/* Destructor */
		~Player();


		/* Comienza el turno. Si es el turno del jugador entonces,
		   habilita los handlers, sino muestra los movimientos realizados
		   por el otro jugador */
		void startTurn(int worm_id, int player_id, float wind);
		
		/* Finaliza el turno del jugador actual */
		void endTurn();

		/* Finaliza el juego */
		void endGame(const std::string& winner);

		/* Cambia el arma actual por la espeificada */
		void changeWeapon(std::string weapon);
		
		/* Realiza el disparo del arma con el angulo, potencia 
		   y tiempo pasados */
		void shoot(int angle, int power, int time);
		
		/* Realiza el disparo del arma en la posicion pasada */
		void shoot(Position position);
		
		/* Reproduce el sonido de falta de tiempo */
		void playTickTime();
		
		/* Devuelve la lista de los elementos presentes en la vista */
		ViewsList& getViewsList();

		/* Devuelve la vista */
		ScreenView& getScreen();

		/* Devuelve la lista de armas */
		WeaponList& getWeapons();

		/* Devuelve el protocolo */
		ClientProtocol& getProtocol();

		/* Devuelve el music player */
		MusicPlayer& getMusicPlayer();

		/* Devuelve el turno */
		Turn& getTurn();
};

#endif

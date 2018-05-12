#ifndef __CLIENTPLAYER_H__
#define __CLIENTPLAYER_H__

#include <memory>
#include "client_Protocol.h"
#include "WorldView.h"
#include "client_Turn.h"
#include "client_Timer.h"
#include "client_Weapon.h"
#include "Position.h"

class Player {
	private:
		ClientProtocol& protocol;
		WorldView& world;
		int32_t weapons_time;
		int32_t actual_angle;
		int actual_dir;
		Weapon actual_weapon;
		std::unique_ptr<Turn> turn;
		std::unique_ptr<Timer> timer;
		
		void disable_attack_handlers();

	public:
		Player(ClientProtocol& protocol, WorldView& world);
		~Player();

		void startTurn(int id);
		void endTurn();
		
		void shoot(int32_t power);
		void shoot(Position position);
		
		bool complete_key_press_handler(GdkEventKey* key_event);
		
		bool movement_key_press_handler(GdkEventKey* key_event);
		
		bool complete_key_release_handler(GdkEventKey* key_event);
		
		bool on_button_press_event(GdkEventButton *event);
		
		Gtk::ScrolledWindow& getWindow();
};

#endif

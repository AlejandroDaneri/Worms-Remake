#ifndef __HANDLERS__H__
#define __HANDLERS__H__

#include "client_Timer.h"
#include <gdk/gdk.h>

class Player;
class ViewsList;
class WeaponList;
class WorldView;

class Handlers{
	private:
		Player& player;
		ViewsList& view_list;
		WeaponList& weapons;
		WorldView& world;

		bool has_shoot;
		int current_angle;
		int weapons_time;

		std::unique_ptr<Timer> timer;


	public:
		Handlers(Player& player, ViewsList& view_list, WeaponList& weapons, WorldView& world);

		~Handlers();

		bool movement_key_press_handler(GdkEventKey* key_event);

		bool complete_key_press_handler(GdkEventKey* key_event);

		bool complete_key_release_handler(GdkEventKey* key_event);

		bool on_button_press_event(GdkEventButton* event);

		bool inactive_key_handler(GdkEventKey* key_event);

		bool inactive_button_handler(GdkEventButton *event);

		void enable_all();

		void disable_all();

		void disable_attack_handlers();

		void timerStopped(int power);

		int getCurrentAngle() const;
};

#endif

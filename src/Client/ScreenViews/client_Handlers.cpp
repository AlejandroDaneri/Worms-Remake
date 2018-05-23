#include "Handlers.h"
#include "client_Player.h"
#include <gtkmm/adjustment.h>
#include <gdk/gdkkeysyms.h>

//const int LEFT_ARROW = 0xff51;
//const int UP_ARROW = 0xff52;
//const int RIGHT_ARROW = 0xff53;
//const int DOWN_ARROW = 0xff54;
//const int ENTER = 0xff0d;
//const int BACK = 0xff08;
const char SPACE = ' ';
const int WEAPONS_TIME = 5;
const char ASCII_OFFSET = 48;
const char ASCII_1 = 49;
const char ASCII_5 = 53;
const int MAX_TIME = 5000;
const int DEFAULT_ANGLE = 45;
const int MAX_ANGLE = 90;
const int MIN_ANGLE = -90;

Handlers::Handlers(Player& player, ViewsList& view_list, WeaponList& weapons, WorldView& world):
	player(player), view_list(view_list), weapons(weapons), world(world){
		this->timer.reset(new Timer(*this, MAX_TIME));
	}

Handlers::~Handlers(){
	this->timer->stop();
	this->timer->join();
}

void Handlers::enable_all(){
	this->weapons_time = WEAPONS_TIME;
	this->current_angle = DEFAULT_ANGLE;
	this->has_shoot = false;

	this->world.getWindow().get_parent()->get_parent()->signal_key_press_event().connect(sigc::mem_fun(*this, &Handlers::complete_key_press_handler));
	this->world.getWindow().get_parent()->get_parent()->signal_key_release_event().connect(sigc::mem_fun(*this, &Handlers::complete_key_release_handler));
	this->world.getWindow().signal_button_press_event().connect(sigc::mem_fun(*this, &Handlers::on_button_press_event));
}

void Handlers::disable_all() {
	this->world.getWindow().get_parent()->get_parent()->signal_key_press_event().connect(sigc::mem_fun(*this, &Handlers::inactive_key_handler));
	this->world.getWindow().get_parent()->get_parent()->signal_key_release_event().connect(sigc::mem_fun(*this, &Handlers::inactive_key_handler));
	this->world.getWindow().signal_button_press_event().connect(sigc::mem_fun(*this, &Handlers::inactive_button_handler));
}

void Handlers::timerStopped(int power){
	this->player.shoot(this->current_angle, power, this->weapons_time);
}

bool Handlers::movement_key_press_handler(GdkEventKey* key_event) {
	if (key_event->keyval == GDK_KEY_Left) {
		this->player.getProtocol().send_move_action(MOVE_LEFT);
		this->view_list.removeScopeVisibility();
	} else if (key_event->keyval == GDK_KEY_Right) {
		this->player.getProtocol().send_move_action(MOVE_RIGHT);
		this->view_list.removeScopeVisibility();
	} else if (key_event->keyval == GDK_KEY_Return) {
		this->player.getProtocol().send_move_action(JUMP);
		this->view_list.removeScopeVisibility();
	} else if (key_event->keyval == GDK_KEY_BackSpace) {
		this->player.getProtocol().send_move_action(ROLLBACK);
		this->view_list.removeScopeVisibility();
	}
	return true;
}

bool Handlers::complete_key_press_handler(GdkEventKey* key_event) {
	this->movement_key_press_handler(key_event);
	if (key_event->keyval == GDK_KEY_Up) {
		if (this->current_angle < MAX_ANGLE) {
			this->current_angle += 5;
		}
		if (this->weapons.get_actual_weapon().hasScope()) {
			this->view_list.updateScope(this->current_angle);
		}
	} else if (key_event->keyval == GDK_KEY_Down) {
		if (this->current_angle > MIN_ANGLE) {
			this->current_angle -= 5;
		}
		if (this->weapons.get_actual_weapon().hasScope()) {
			this->view_list.updateScope(this->current_angle);
		}
	} else if (key_event->keyval >= ASCII_1 && key_event->keyval <= ASCII_5) {
		this->weapons_time = key_event->keyval - ASCII_OFFSET;
	} else if (key_event->keyval == SPACE && key_event->type == GDK_KEY_PRESS) {
		if (this->weapons.get_actual_weapon().isSelfDirected()) {
			return true;
		}
		if (!this->weapons.get_actual_weapon().hasAmmo()) {
			///////////////////////// Hacer sonido u otra cosa
			return true;
		}
		if (this->has_shoot) {
			return true;
		}
		this->has_shoot = true;
		printf("se apreto la barra\n");
		if (!this->weapons.get_actual_weapon().hasVariablePower()) {
			this->player.shoot(this->current_angle, -1, this->weapons_time);
		} else {
			this->timer->join();
			this->timer.reset(new Timer(*this, MAX_TIME));
			this->timer->start(); 
			printf("Salio\n");
		}
	}
	return true;
}

bool Handlers::complete_key_release_handler(GdkEventKey* key_event) {
	if (key_event->keyval == SPACE && key_event->type == GDK_KEY_RELEASE) {
		if (this->weapons.get_actual_weapon().isSelfDirected()) {
			return true;
		}
		if (!this->weapons.get_actual_weapon().hasVariablePower()) {
			return true;
		}
		if (!this->weapons.get_actual_weapon().hasAmmo()) {
			return true;
		}
		printf("se solto la barra\n");
		printf("Timer stop\n");
		this->timer->stop();
	} else if (key_event->keyval == GDK_KEY_Left) {}
		///////////////////////// ANIMACION DE SACAR EL ARMA
	else if (key_event->keyval == GDK_KEY_Right) {}
		///////////////////////// ANIMACION DE SACAR EL ARMA
	return true;
}

bool Handlers::on_button_press_event(GdkEventButton* event) {
	if (!this->weapons.get_actual_weapon().isSelfDirected()) {
		return true;
	}
	if (!this->weapons.get_actual_weapon().hasAmmo()) {
		return true;
	}
	if (this->has_shoot) {
		return true;
	}
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1)) {
		int x = (int)event->x;
		int y = (int)event->y;
		x += this->world.getWindow().get_hadjustment()->get_value();
		y += this->world.getWindow().get_vadjustment()->get_value();
		printf("x = %i   y=%i\n", x,y);
		this->has_shoot = true;
		Position position(x, y);
		this->player.shoot(position);
	}
	return true;
}

bool Handlers::inactive_key_handler(GdkEventKey* key_event) {
	return true;
}

bool Handlers::inactive_button_handler(GdkEventButton *event) {
	return true;
}

int Handlers::getCurrentAngle() const{
	return this->current_angle;
}

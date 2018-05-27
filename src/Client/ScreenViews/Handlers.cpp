#include "Handlers.h"
#include "Player.h"
#include <gtkmm/adjustment.h>
#include <gdk/gdkkeysyms.h>
#include "ViewTransformer.h"

const char SPACE = ' ';
const int WEAPONS_TIME = 5;
const char ASCII_OFFSET = 48;
const char ASCII_1 = 49;
const char ASCII_5 = 53;
const int MAX_TIME = 5000;
const int DEFAULT_ANGLE = 48;
const int MAX_ANGLE = 90;
const int MIN_ANGLE = -90;

Handlers::Handlers(Player& player, ViewsList& view_list, WeaponList& weapons, WorldView& world):
	player(player), view_list(view_list), weapons(weapons), world(world),
	timer(*this, MAX_TIME) {}

Handlers::~Handlers() {}

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
        if (!this->weapons.get_current_weapon().hasScope()) {
            return true;
        }
		if (this->current_angle < MAX_ANGLE) {
			this->current_angle += 6;
			this->player.getProtocol().updateScope(this->current_angle);
		}
	} else if (key_event->keyval == GDK_KEY_Down) {
		if (!this->weapons.get_current_weapon().hasScope()) {
		    return true;
		}
		if (this->current_angle > MIN_ANGLE) {
			this->current_angle -= 6;
			this->player.getProtocol().updateScope(this->current_angle);
		}
	} else if (key_event->keyval >= ASCII_1 && key_event->keyval <= ASCII_5) {
		this->weapons_time = key_event->keyval - ASCII_OFFSET;
	} else if (key_event->keyval == SPACE && key_event->type == GDK_KEY_PRESS) {
		if (this->weapons.get_current_weapon().isSelfDirected()) {
			return true;
		}
		if (!this->weapons.get_current_weapon().hasAmmo()) {
			///////////////////////// Hacer sonido u otra cosa
			return true;
		}
		if (this->has_shoot) {
			return true;
		}
		this->has_shoot = true;
		if (!this->weapons.get_current_weapon().hasVariablePower()) {
			this->player.shoot(this->current_angle, -1, this->weapons_time);
		} else {
			this->timer.start();
		}
	}
	return true;
}

bool Handlers::complete_key_release_handler(GdkEventKey* key_event) {
	if (key_event->type == GDK_KEY_RELEASE) {
		if (key_event->keyval == SPACE) {
			if (this->weapons.get_current_weapon().isSelfDirected()) {
				return true;
			}
			if (!this->weapons.get_current_weapon().hasVariablePower()) {
				return true;
			}
			if (!this->weapons.get_current_weapon().hasAmmo()) {
                this->player.getMusicPlayer().playNoAmmo();
                return true;
			}
			this->timer.stop();
		}
	}
	return true;
}

bool Handlers::on_button_press_event(GdkEventButton* event) {
	if (!this->weapons.get_current_weapon().isSelfDirected()) {
		return true;
	}
	if (!this->weapons.get_current_weapon().hasAmmo()) {
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
		Position position(x, y);
		Position newPosition = ViewTransformer(this->world.getLayout()).transformToPosition(position);
		this->has_shoot = true;
		this->player.shoot(newPosition);
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

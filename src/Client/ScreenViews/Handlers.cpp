#include "Handlers.h"
#include <gtkmm/adjustment.h>
#include <gdk/gdkkeysyms.h>
#include "Player.h"
#include "ViewTransformer.h"
#include "WeaponNames.h"

const char SPACE = ' ';
const int WEAPONS_TIME = 5;
const char ASCII_OFFSET = 48;
const char ASCII_1 = 49;
const char ASCII_5 = 53;
const int MAX_TIME = 5000;
const int DEFAULT_ANGLE = 48;
const int ANGLE_STEP = 6;

Handlers::Handlers(Player& player, ViewsList& view_list, WeaponList& weapons, WorldView& world):
	player(player), view_list(view_list), weapons(weapons), world(world),
	timer(*this, MAX_TIME) {}

Handlers::~Handlers() {}

void Handlers::enableAll(){
	this->weapons_time = WEAPONS_TIME;
	this->current_angle = DEFAULT_ANGLE;
	this->has_shoot = false;

	this->world.getWindow().get_parent()->get_parent()->signal_key_press_event().connect(sigc::mem_fun(*this,
                                                                                                       &Handlers::completeKeyPressHandler));
	this->world.getWindow().get_parent()->get_parent()->signal_key_release_event().connect(sigc::mem_fun(*this,
                                                                                                         &Handlers::completeKeyReleaseHandler));
	this->world.getWindow().signal_button_press_event().connect(sigc::mem_fun(*this, &Handlers::onButtonPressEvent));
}

void Handlers::disableAll() {
	this->world.getWindow().get_parent()->get_parent()->signal_key_press_event().connect(sigc::mem_fun(*this,
                                                                                                       &Handlers::inactiveKeyHandler));
	this->world.getWindow().get_parent()->get_parent()->signal_key_release_event().connect(sigc::mem_fun(*this,
                                                                                                         &Handlers::inactiveKeyHandler));
	this->world.getWindow().signal_button_press_event().connect(sigc::mem_fun(*this, &Handlers::inactiveButtonHandler));
}

void Handlers::timerStopped(int power){
	this->player.shoot(this->current_angle, power, this->weapons_time);
}

bool Handlers::movementKeyPressHandler(GdkEventKey *key_event) {
	if (key_event->keyval == GDK_KEY_Left) {
        this->player.getProtocol().sendMoveAction(MOVE_LEFT);
	} else if (key_event->keyval == GDK_KEY_Right) {
        this->player.getProtocol().sendMoveAction(MOVE_RIGHT);
	} else if (key_event->keyval == GDK_KEY_Return) {
        this->player.getProtocol().sendMoveAction(JUMP);
	} else if (key_event->keyval == GDK_KEY_BackSpace) {
        this->player.getProtocol().sendMoveAction(ROLLBACK);
	}
	return true;
}

bool Handlers::completeKeyPressHandler(GdkEventKey *key_event) {
    this->movementKeyPressHandler(key_event);
	if (key_event->keyval == GDK_KEY_Up) {
        if (!this->weapons.getCurrentWeapon().hasScope()) {
            return true;
        }
		if (this->current_angle < MAX_WEAPON_ANGLE) {
			this->current_angle += ANGLE_STEP;
			this->player.getProtocol().updateScope(this->current_angle);
		}
	} else if (key_event->keyval == GDK_KEY_Down) {
		if (!this->weapons.getCurrentWeapon().hasScope()) {
		    return true;
		}
		if (this->current_angle > MIN_WEAPON_ANGLE) {
			this->current_angle -= ANGLE_STEP;
			this->player.getProtocol().updateScope(this->current_angle);
		}
	} else if (key_event->keyval >= ASCII_1 && key_event->keyval <= ASCII_5) {
		this->weapons_time = key_event->keyval - ASCII_OFFSET;
	} else if (key_event->keyval == SPACE && key_event->type == GDK_KEY_PRESS) {
		if (this->weapons.getCurrentWeapon().isSelfDirected()) {
			return true;
		}
		if (!this->weapons.getCurrentWeapon().hasAmmo()) {
			return true;
		}
		if (this->has_shoot) {
			return true;
		}
		this->has_shoot = true;
		if (!this->weapons.getCurrentWeapon().hasVariablePower()) {
			this->player.shoot(this->current_angle, -1, this->weapons_time);
		} else {
			this->timer.start();
		}
	}
	return true;
}

bool Handlers::completeKeyReleaseHandler(GdkEventKey *key_event) {
	if (key_event->type == GDK_KEY_RELEASE) {
		if (key_event->keyval == SPACE) {
			if (this->weapons.getCurrentWeapon().isSelfDirected()) {
				return true;
			}
			if (!this->weapons.getCurrentWeapon().hasVariablePower()) {
				return true;
			}
			if (!this->weapons.getCurrentWeapon().hasAmmo()) {
                this->player.getMusicPlayer().playNoAmmo();
                return true;
			}
			this->timer.stop();
		}
	}
	return true;
}

bool Handlers::onButtonPressEvent(GdkEventButton *event) {
	if (!this->weapons.getCurrentWeapon().isSelfDirected()) {
		return true;
	}
	if (!this->weapons.getCurrentWeapon().hasAmmo()) {
		this->player.getMusicPlayer().playNoAmmo();
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

bool Handlers::inactiveKeyHandler(GdkEventKey *key_event) {
	return true;
}

bool Handlers::inactiveButtonHandler(GdkEventButton *event) {
	return true;
}

int Handlers::getCurrentAngle() const{
	return this->current_angle;
}

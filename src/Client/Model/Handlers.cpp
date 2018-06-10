#include "Handlers.h"
#include <gtkmm/adjustment.h>
#include <gdk/gdkkeysyms.h>
#include "Player.h"
#include "ViewPositionTransformer.h"
#include "WeaponNames.h"

const char SPACE = ' ';
const int WEAPONS_DEFAULT_TIME = 3;
const char ASCII_OFFSET = 48;
const char ASCII_1 = 49;
const char ASCII_5 = 53;
const int MAX_TIME = 3000;
const int ANGLE_STEP = 6;

Handlers::Handlers(Player& player, ViewsList& view_list, WeaponList& weapons,
				   WorldView& world) :
		player(player), view_list(view_list), weapons(weapons), world(world),
		scroll_handler(world.getWindow()), power_accumulator(*this, MAX_TIME) {
	this->has_shoot = false;
	this->current_angle = DEFAULT_ANGLE;
	this->weapons_time = WEAPONS_DEFAULT_TIME;
	this->enabled = false;
}

Handlers::~Handlers() {}

void Handlers::enableAll() {
	this->weapons_time = WEAPONS_DEFAULT_TIME;
	this->current_angle = DEFAULT_ANGLE;
	this->has_shoot = false;
	this->enabled = true;

	this->player.getProtocol().updateScope(DEFAULT_ANGLE);

	Gtk::Container* window = this->world.getWindow().get_parent()->get_parent();

	window->set_can_focus(true);
	window->grab_focus();

	window->signal_key_press_event().connect(
			sigc::mem_fun(*this, &Handlers::keyPressHandler));
	window->signal_key_release_event().connect(
			sigc::mem_fun(*this, &Handlers::keyReleaseHandler));
	this->world.getWindow().signal_button_press_event().connect(
			sigc::mem_fun(*this, &Handlers::onButtonPressEvent));
}

void Handlers::disableAll() {
	this->enabled = false;
}

bool Handlers::isEnabled() const {
	return this->enabled;
}

void Handlers::powerAccumStopped(int power) {
	this->player.shoot(this->current_angle, power, this->weapons_time);
}

bool Handlers::keyPressHandler(GdkEventKey* key_event) {
	if (!this->enabled) {
		return true;
	}

	if (key_event->keyval == GDK_KEY_Left) {
		this->player.getProtocol().sendMoveAction(MOVE_LEFT);
	} else if (key_event->keyval == GDK_KEY_Right) {
		this->player.getProtocol().sendMoveAction(MOVE_RIGHT);
	} else if (key_event->keyval == GDK_KEY_Return) {
		this->player.getProtocol().sendMoveAction(JUMP);
	} else if (key_event->keyval == GDK_KEY_BackSpace) {
		this->player.getProtocol().sendMoveAction(ROLLBACK);
	} else if (key_event->keyval == GDK_KEY_Up) {
		if (!this->weapons.getCurrentWeapon().hasScope()) {
			return true;
		}
		if (this->current_angle < MAX_WEAPON_ANGLE) {
			this->current_angle += ANGLE_STEP;
		}
		this->player.getProtocol().updateScope(this->current_angle);
	} else if (key_event->keyval == GDK_KEY_Down) {
		if (!this->weapons.getCurrentWeapon().hasScope()) {
			return true;
		}
		if (this->current_angle > MIN_WEAPON_ANGLE) {
			this->current_angle -= ANGLE_STEP;
		}
		this->player.getProtocol().updateScope(this->current_angle);
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
			this->power_accumulator.start();
		}
	}
	return true;
}

bool Handlers::keyReleaseHandler(GdkEventKey* key_event) {
	if (!this->enabled) {
		return true;
	}

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
			this->power_accumulator.stop();
		}
	}
	return true;
}

bool Handlers::onButtonPressEvent(GdkEventButton* event) {
	if (!this->enabled) {
		return true;
	}

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
		float x = event->x;
		float y = event->y;
		x += this->world.getWindow().get_hadjustment()->get_value();
		y += this->world.getWindow().get_vadjustment()->get_value();
		Position position(x, y);
		Position newPosition = ViewPositionTransformer(
				this->world.getLayout()).transformToPosition(position);
		this->has_shoot = true;
		this->player.shoot(newPosition);
	}
	return true;
}

int Handlers::getCurrentAngle() const {
	return this->current_angle;
}

void Handlers::stop() {
	this->scroll_handler.stop();
}

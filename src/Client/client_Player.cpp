#include "client_Player.h"
#include "client_Bazooka.h"
#include "ViewTransformer.h"
#include <iostream>

#define LEFT_ARROW 0xff51
#define UP_ARROW 0xff52
#define RIGHT_ARROW 0xff53
#define DOWN_ARROW 0xff54
#define SPACE ' '
#define ENTER 0xff0d
#define BACK 0xff08
#define WEAPONS_TIME 5
#define ASCII_OFFSET 48
#define ASCII_1 49
#define ASCII_5 53 
#define MAX_TIME 5000 

Player::Player(ClientProtocol& protocol, WorldView& world) : 
	protocol(protocol), world(world), weapons_time(WEAPONS_TIME),
	actual_angle(0), actual_dir(1), actual_weapon(Bazooka(10)) {
	this->weapons.add(std::move(Bazooka(10)));
	// Por ahora solo tiene esta hasta que agreguemos la parte de inicializar
	// las armas al empezar el juego
}

Player::~Player() {
	printf("Se destruyo\n");
}

void Player::startTurn(int id){
	//setear handlers
	this->weapons_time = WEAPONS_TIME;
	this->actual_angle = 0;
	this->turn = std::move(std::unique_ptr<Turn>(new Turn(*this)));
	this->world.enable_all_handlers(*this);
	// mandar arma
	this->turn->run();
}

void Player::endTurn() {
	///////Sacar los handlers
	this->world.disable_handlers();
	this->protocol.send_end_turn();
	this->turn->join();
}

void Player::disable_attack_handlers() {
	this->world.enable_movement_handlers(*this);
	this->turn->reduceTime();
	this->actual_weapon.shoot();
}

void Player::change_weapon(std::string weapon) {
	//this->actual_weapon = this->weapons.get(weapon);
}

void Player::shoot(Position position) {
	this->disable_attack_handlers();
	Position newPosition = ViewTransformer().transformToPosition(position);
	this->protocol.send_weapon_self_directed_shoot(newPosition);
}

void Player::shoot(int32_t power) {
	//Handler verifica si tiene balas y todo eso
	this->disable_attack_handlers();
	if (this->actual_weapon.hasVariablePower())
		this->timer->join();
	int32_t angle = this->actual_angle; 
	if (!this->actual_weapon.isTimed())
		this->weapons_time = -1;
	if (this->actual_dir == -1)
		angle = 180 - angle; 
	if (!this->actual_weapon.hasScope())
		angle = 500;
	// Elimino los handlers de disparo
	this->protocol.send_weapon_shoot(angle, power, this->weapons_time);
}

bool Player::movement_key_press_handler(GdkEventKey* key_event) {
	if (key_event->keyval == LEFT_ARROW)
		this->protocol.send_move_action(MOVE_LEFT);
	else if (key_event->keyval == RIGHT_ARROW)
		this->protocol.send_move_action(MOVE_RIGHT);
	else if (key_event->keyval == ENTER)
		this->protocol.send_move_action(JUMP);
	else if (key_event->keyval == BACK)
		this->protocol.send_move_action(ROLLBACK);
	return true;
}

bool Player::complete_key_press_handler(GdkEventKey* key_event) {
	// Por ahora lo dejo asi.
	//std::cout << "key event = " << key_event->keyval << std::endl;
	this->movement_key_press_handler(key_event);
	if (key_event->keyval == UP_ARROW) {
		if (this->actual_angle < 90)
			this->actual_angle++; /////////////////////////////////// ACTUALIZAR LINEA DE TIRO
		this->protocol.send_move_action(EXTEND_ANGLE);
	} else if (key_event->keyval == DOWN_ARROW) {
		if (this->actual_angle > -90)
			this->actual_angle--;
		this->protocol.send_move_action(REDUCE_ANGLE);
	} else if (key_event->keyval >= ASCII_1 && key_event->keyval <= ASCII_5) {
		this->weapons_time = key_event->keyval - ASCII_OFFSET;
	} else if (key_event->keyval == SPACE) {
		if (!this->actual_weapon.hasAmmo())
			///////////////////////// Hacer sonido u otra cosa
			return true; 
		if (!this->actual_weapon.hasVariablePower())
			this->shoot(0);
		else {
			this->timer = std::move(std::unique_ptr<Timer>(new Timer(*this, MAX_TIME)));
			this->timer->run();
		}
	}
	return true;
}

bool Player::complete_key_release_handler(GdkEventKey* key_event) {
	//std::cout << "Se solto la barra.  key event = " << key_event->keyval << std::endl;
	if (key_event->keyval == SPACE) {
		this->timer->stop();
		this->shoot(this->timer->getTime());
	}
	return true;
}

bool Player::on_button_press_event(GdkEventButton *event) {
	if (!this->actual_weapon.isSelfDirected())
		return true;
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1)) {
		Position position((int)event->x, (int)event->y);
		this->shoot(position);
	}
	return true;
}

Gtk::HBox& Player::getWindow() {
	return this->world.getWindow();
}

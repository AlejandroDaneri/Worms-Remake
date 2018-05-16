#include "client_Player.h"
#include "client_Bazooka.h"
#include "ViewTransformer.h"
#include <gtkmm/adjustment.h>
#include <iostream> ///////////////////////////////////////////////////////////////////

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

Player::Player(ClientProtocol& protocol) : 
	protocol(protocol), weapons_time(WEAPONS_TIME),
	actual_angle(45), actual_dir(1), world(*this), weapons_view(this->weapons, *this),
	screen(this->world, this->weapons_view), view_list(this->world),
	data_receiver(this->view_list, *this, protocol) {

	this->protocol.receiveGirders(this->view_list);
	this->protocol.receiveWeaponsAmmo(this->weapons);
	this->weapons_view.update();
	this->data_receiver.start();
	this->turn = std::move(std::unique_ptr<Turn>(new Turn(*this)));
	this->timer = std::move(std::unique_ptr<Timer>(new Timer(*this, MAX_TIME)));
}

Player::~Player() {
	std::cout << "destruyo" << std::endl;
	this->turn->stop();
	this->turn->join();
	this->timer->stop();
	this->timer->join();
	this->data_receiver.stop();
	this->data_receiver.join();
}

void Player::startTurn(int id){
	//setear handlers
	this->weapons_time = WEAPONS_TIME;
	this->actual_angle = 45;
	this->turn->join();
	this->turn = std::move(std::unique_ptr<Turn>(new Turn(*this)));
	this->world.enable_all_handlers();
	// mandar arma
	this->has_shoot = false;

	//this->protocol.send_change_weapon("Bazooka");///////////////////////////////////////////////////////////////////////////
	//this->weapons.change_weapon("Bazooka"); ///////////////////////////////////////////////////////////////////////////////////
	this->change_weapon(this->weapons.get_actual_weapon().getName());
	std::cout << "key event = " << this->weapons.get_actual_weapon().getName() << std::endl;
	this->turn->start();
}

void Player::endTurn() {
	///////Sacar los handlers
	this->world.disable_handlers();
	this->protocol.send_end_turn();
	//this->turn->join();////////////////////////////////////////////Rompe en este join
}

void Player::disable_attack_handlers() {
	this->world.enable_movement_handlers();
	this->turn->reduceTime();
	this->weapons.get_actual_weapon().shoot();
}

void Player::change_weapon(std::string weapon) {
	this->weapons.change_weapon(weapon);
	this->protocol.send_change_weapon(weapon);
}

void Player::shoot(Position position) {
	this->disable_attack_handlers();
	Position newPosition = ViewTransformer().transformToPosition(position);
	this->protocol.send_weapon_self_directed_shoot(newPosition);
}

void Player::play_tick_time() {
	///////////////////////////////////// Reproducir sonido de falta de tiempo
}

void Player::shoot(int32_t power) { ///////////////////////////////////// Creo que hay que poner un mutex
	// Elimino los handlers de disparo
	printf("shoot\n");
	this->disable_attack_handlers();
	int32_t angle = this->actual_angle;
	//if (this->weapons.get_actual_weapon().hasVariablePower())
		//this->timer->join();
	if (!this->weapons.get_actual_weapon().isTimed())
		this->weapons_time = -1;
	if (!this->weapons.get_actual_weapon().hasScope())
		angle = 500;
	printf("angle = %i\n",this->actual_angle);
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
	//printf("handler de movimiento\n");
	this->movement_key_press_handler(key_event);
	if (key_event->keyval == UP_ARROW) {
		printf("Arriba\n");
		if (this->actual_angle < 90)
			this->actual_angle++; /////////////////////////////////// ACTUALIZAR LINEA DE TIRO
	} else if (key_event->keyval == DOWN_ARROW) {
		//printf("Abajo\n");
		if (this->actual_angle > -90)
			this->actual_angle--;
	} else if (key_event->keyval >= ASCII_1 && key_event->keyval <= ASCII_5) {
		this->weapons_time = key_event->keyval - ASCII_OFFSET;
	} else if (key_event->keyval == SPACE && key_event->type == GDK_KEY_PRESS) {
		if (this->weapons.get_actual_weapon().isSelfDirected())
			return true;
		if (!this->weapons.get_actual_weapon().hasAmmo())
			///////////////////////// Hacer sonido u otra cosa
			return true;
		if (this->has_shoot)
			return true;
		this->has_shoot = true;
		printf("se apreto la barra\n");
		if (!this->weapons.get_actual_weapon().hasVariablePower())
			this->shoot(-1); /////////////////////////////////////////////////////Ver que onda
		else {
			this->timer->join();
			this->timer = std::move(std::unique_ptr<Timer>(new Timer(*this, MAX_TIME)));
			this->timer->start(); //////////////////////////////////////////////////////// Shoot minimo de 1000
			//this->shoot(5000);
			printf("Salio\n");
		}
	}
	return true;
}

bool Player::complete_key_release_handler(GdkEventKey* key_event) {
	//std::cout << "Se solto la barra.  key event = " << key_event->keyval << std::endl;
	if (key_event->keyval == SPACE && key_event->type == GDK_KEY_RELEASE) {
		printf("se solto la barra\n");
		if (this->weapons.get_actual_weapon().isSelfDirected())
			return true;
		if (!this->weapons.get_actual_weapon().hasVariablePower())
			return true;
		if (!this->weapons.get_actual_weapon().hasAmmo())
			return true;
		//printf("se solto la barra\n");
		if (key_event->type == GDK_KEY_PRESS)
			return true;
		printf("Timer stop\n");
		this->timer->stop();
	} else if (key_event->keyval == LEFT_ARROW) {}
		///////////////////////// ANIMACION DE SACAR EL ARMA
	else if (key_event->keyval == RIGHT_ARROW) {}
		///////////////////////// ANIMACION DE SACAR EL ARMA
	return true;
}

bool Player::on_button_press_event(GdkEventButton *event) {
	//printf("se apretó el mouse\n");
	if (!this->weapons.get_actual_weapon().isSelfDirected())
		return true;
	if (!this->weapons.get_actual_weapon().hasAmmo())
		return true;
	if (this->has_shoot)
		return true;
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1)) {
		int x = (int)event->x;
		int y = (int)event->y;
		x += this->world.getWindow().get_hadjustment()->get_value();
		y += this->world.getWindow().get_vadjustment()->get_value();
		printf("x = %i   y=%i\n", x,y);
		this->has_shoot = true;
		Position position(x, y);
		this->shoot(position);
	}
	return true;
}

Gtk::HBox& Player::getWindow() {
	return this->screen.getWindow();
}

WorldView& Player::getWorld() {
	return this->world;
}

ViewsList& Player::getViewList() {
	return this->view_list;
}


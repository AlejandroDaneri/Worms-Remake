#include "client_Player.h"
#include "ViewTransformer.h"
#include <iostream> ///////////////////////////////////////////////////////////////////

const int NO_ANGLE = 500;

Player::Player(ClientProtocol protocol, const std::string& name): 
	protocol(std::move(protocol)), name(name), weapons_view(this->weapons, *this),
	screen(this->world, this->weapons_view, this->turn_label, this->players_list),
	view_list(this->world, *this, this->players_list),
	data_receiver(this->view_list, *this, this->protocol),
	handlers(*this, this->view_list, this->weapons, this->world) {

	this->protocol.receivePlayers(this->players_list);
	this->protocol.receiveGirders(this->view_list);
	this->protocol.receiveWeaponsAmmo(this->weapons);
	this->weapons_view.update();
	this->data_receiver.start();
	this->turn.reset(new Turn(*this, this->turn_label));
}

Player::~Player() {
	std::cout << "destruyo" << std::endl;
	this->turn->stop();
	this->turn->join();
	this->data_receiver.stop();
	this->data_receiver.join();
}

void Player::startTurn(int worm_id, int player_id){
	this->view_list.setCurrentWorm(worm_id);
	this->turn->join();
	this->turn.reset(new Turn(*this, this->turn_label));
	const std::string& current_player = this->players_list.getPlayer(player_id);
	if (current_player == this->name){
		//Es mi turno
		this->handlers.enable_all();
		// mandar arma
		this->change_weapon(this->weapons.get_actual_weapon().getName());
		std::cout << "key event = " << this->weapons.get_actual_weapon().getName() << std::endl;
		this->turn_label.beginTurn();
		this->turn->start();
	} else {
		this->turn_label.beginTurn(current_player);
	}
}

void Player::endTurn() {
	this->turn_label.endTurn();
	this->handlers.disable_all();
	this->view_list.removeScopeVisibility();
	this->protocol.send_end_turn();
}

void Player::damageReceived(){
	this->turn->stop();
}

void Player::disable_attack_handlers() {
	this->handlers.disable_attack_handlers();
	this->turn->reduceTime();
	this->weapons.get_actual_weapon().shoot();
}

void Player::change_weapon(std::string weapon) {
	this->weapons.change_weapon(weapon);
	this->protocol.send_change_weapon(weapon);
	if (this->weapons.get_actual_weapon().hasScope()) {
		this->view_list.updateScope(this->handlers.getCurrentAngle());
	} else {
		this->view_list.removeScopeVisibility();
	}
}

void Player::shoot(Position position) {
	this->disable_attack_handlers();
	Position newPosition = ViewTransformer().transformToPosition(position);
	this->protocol.send_weapon_self_directed_shoot(newPosition);
	this->weapons_view.updateAmmo(this->weapons.get_actual_weapon());
}

void Player::play_tick_time() {
	printf("Tick\n");
	///////////////////////////////////// Reproducir sonido de falta de tiempo
}

void Player::shoot(int angle, int power, int time) {
	// Elimino los handlers de disparo
	printf("shoot\n");
	this->disable_attack_handlers();
	if (!this->weapons.get_actual_weapon().isTimed()) {
		time = -1;
	}
	if (!this->weapons.get_actual_weapon().hasScope()) {
		angle = NO_ANGLE;
	}
	this->protocol.send_weapon_shoot(angle, power, time);
	this->view_list.removeScopeVisibility();
	this->weapons_view.updateAmmo(this->weapons.get_actual_weapon());
}



Gtk::Container& Player::getWindow() {
	return this->screen.getWindow();
}

WorldView& Player::getWorld() {
	return this->world;
}

ViewsList& Player::getViewList() {
	return this->view_list;
}

ClientProtocol& Player::getProtocol(){
	return this->protocol;
}

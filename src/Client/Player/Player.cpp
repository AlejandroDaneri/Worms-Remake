#include "Player.h"
#include "WeaponNames.h"

const int NO_ANGLE = 500;

Player::Player(ClientProtocol protocol, const std::string& name, Gtk::Window& window):
	protocol(std::move(protocol)), name(name),
	screen(*this, this->weapons, this->turn_label, this->players_list),
    turn(*this, this->turn_label),
	view_list(this->screen.getWorld(), *this, this->players_list, musicPlayer),
	data_receiver(this->view_list, *this, this->protocol),
	handlers(*this, this->view_list, this->weapons, this->screen.getWorld()){

	this->protocol.receive_char();
	this->musicPlayer.playMusic();
	this->protocol.receivePlayers(this->players_list);
	this->protocol.receiveGirders(this->view_list);
	this->protocol.receiveWeaponsAmmo(this->weapons);
	this->screen.getWeaponsView().update();
	this->data_receiver.start();

	window.remove();
	window.add(this->screen.getWindow());
	window.show_all();
}

Player::~Player() {
	this->data_receiver.stop();
	this->data_receiver.join();
}

void Player::startTurn(int worm_id, int player_id){
	this->view_list.setCurrentWorm(worm_id);
	const std::string& current_player = this->players_list.getPlayer(player_id);
	if (current_player == this->name){
	    this->musicPlayer.playStartTurnSound();
		//Es mi turno
        this->handlers.enableAll();
		this->change_weapon(this->weapons.getCurrentWeapon().getName());
		this->turn_label.beginTurn();
		this->turn.start();
	} else {
		this->turn_label.beginTurn(current_player);
	}
}

void Player::endTurn() {
	this->turn_label.endTurn();
    this->handlers.disableAll();
	this->view_list.removeScopeVisibility();
    this->protocol.sendEndTurn();
}

void Player::damageReceived(){
	this->turn.stop();
}

void Player::shootWeapon() {
	this->turn.reduceTime();
    this->weapons.getCurrentWeapon().shoot();
    if (this->weapons.getCurrentWeapon().getName() == TELEPORT_NAME) { ////////////////esto no va aca, sino solo lo escucha un jugador
        this->musicPlayer.playTeleportSound();
    } else if (this->weapons.getCurrentWeapon().getName() == BAT_NAME) {
        this->musicPlayer.playBatSound();
    }
}

void Player::change_weapon(std::string weapon) {
    this->weapons.changeWeapon(weapon);
    this->protocol.sendChangeWeapon(weapon);
	if (this->weapons.getCurrentWeapon().hasScope()) {
		this->view_list.updateScope(this->handlers.getCurrentAngle());
	} else {
		this->view_list.removeScopeVisibility();
	}
}

void Player::shoot(Position position) {
	this->shootWeapon();
    this->protocol.sendWeaponSelfDirectedShoot(position);
	this->screen.getWeaponsView().updateAmmo(this->weapons.getCurrentWeapon());
}

void Player::playTickTime() {
	this->musicPlayer.playTickSound();
}

void Player::shoot(int angle, int power, int time) {
	this->shootWeapon();
	if (!this->weapons.getCurrentWeapon().isTimed()) {
		time = -1;
	}
	if (!this->weapons.getCurrentWeapon().hasScope()) {
		angle = NO_ANGLE;
	}
    this->protocol.sendWeaponShoot(angle, power, time);
	this->view_list.removeScopeVisibility();
	this->screen.getWeaponsView().updateAmmo(this->weapons.getCurrentWeapon());
}

WorldView& Player::getWorld() {
	return this->screen.getWorld();
}

ViewsList& Player::getViewList() {
	return this->view_list;
}

ClientProtocol& Player::getProtocol(){
	return this->protocol;
}

MusicPlayer& Player::getMusicPlayer() {
    return this->musicPlayer;
}

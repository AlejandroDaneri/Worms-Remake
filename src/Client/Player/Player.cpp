#include "Player.h"
#include "WeaponNames.h"

Player::Player(ClientProtocol protocol, const std::string& name, Gtk::Window& window):
	protocol(std::move(protocol)), name(name),
	screen(window, *this, this->weapons),
    turn(*this, this->screen.getTurnLabel()),
	view_list(this->screen.getWorld(), *this, this->screen.getPlayersView(), musicPlayer),
	data_receiver(*this),
	handlers(*this, this->view_list, this->weapons, this->screen.getWorld()){

	this->musicPlayer.playMusic();
	this->data_receiver.start();
}

Player::~Player() {
	this->data_receiver.stop();
	this->data_receiver.join();
}

void Player::startTurn(int worm_id, int player_id, float wind){
	this->view_list.setCurrentWorm(worm_id);
	this->screen.getWindView().update(wind);
	const std::string& current_player = this->screen.getPlayersView().getPlayer(player_id);
	if (current_player == this->name){
		//Es mi turno
	    this->musicPlayer.playStartTurnSound();
        this->handlers.enableAll();
        this->changeWeapon(this->weapons.getCurrentWeapon().getName());
		this->screen.getTurnLabel().beginTurn();
		this->turn.start();
	} else {
		this->screen.getTurnLabel().beginTurn(current_player);
	}
}

void Player::endTurn() {
	this->turn.stop();
	this->screen.getTurnLabel().endTurn();
	this->view_list.removeScopeVisibility();
}

void Player::endGame(const std::string& winner){
	this->data_receiver.stop();
	this->screen.getTurnLabel().setWinner(winner, this->name == winner);
    this->view_list.setVictory();
}

void Player::endTurnEarly(){
	//this->turn.stop();
}

void Player::shootWeapon() {
	this->turn.reduceTime();
    this->weapons.getCurrentWeapon().shoot();
}

void Player::changeWeapon(std::string weapon) {
	this->musicPlayer.playSelectWeaponSound();
	this->weapons.changeWeapon(weapon);
    this->protocol.sendChangeWeapon(weapon);
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
		angle = MAX_WEAPON_ANGLE * 8;
	}
    this->protocol.sendWeaponShoot(angle, power, time);
	this->view_list.removeScopeVisibility();
	this->screen.getWeaponsView().updateAmmo(this->weapons.getCurrentWeapon());
}

ViewsList& Player::getViewsList() {
	return this->view_list;
}

ScreenView& Player::getScreen(){
	return this->screen;
}

WeaponList& Player::getWeapons(){
	return this->weapons;
}

ClientProtocol& Player::getProtocol(){
	return this->protocol;
}

MusicPlayer& Player::getMusicPlayer() {
    return this->musicPlayer;
}

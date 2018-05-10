#include "client_Player.h"
#include "client_Turn.h"

#define TIMER 60

Player::Player(){
	////////////////////////////////////
}

Player::~Player(){}

void Player::startTurn(int id){
	//////////////////////////////////////
	//setear handlers
	// mandar arma
	Turno turno(TIMER, *this);
}

void Player::endTurn() {
	///////Sacar los handlers
	//this->world.set_moving_handler(&Player::no_handler);
	//this->protocol.send_end_turn();
}

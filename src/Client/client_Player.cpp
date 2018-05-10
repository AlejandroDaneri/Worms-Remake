#include "client_Player.h"

#define LEFT_ARROW 0xff51
#define UP_ARROW 0xff52
#define RIGHT_ARROW 0xff53
#define DOWN_ARROW 0xff54
#define ENTER '\n'
#define BACK 0xff54

Player::Player(Protocol& protocol, WorldView& world) : 
	protocol(protocol), world(world) {
	this->turn = new Turn(*this);
}
	////////////////////////////////////

Player::~Player() {delete this->turn;}

void Player::startTurn(int id){
	//////////////////////////////////////
	//setear handlers
	//this->world.enable_handlers(*this);
	// mandar arma
	this->turn->run();
}

void Player::endTurn() {
	///////Sacar los handlers
	//this->world.disable_handlers();
	//this->protocol.send_end_turn();
	//this->turn->join();
}

bool Player::complete_handler(GdkEventKey* key_event) {
	// Por ahora lo dejo asi.
	if (key_event->keyval == LEFT_ARROW) {
		this->protocol.send_move_action(MOVE_LEFT);
	} else if (key_event->keyval == RIGHT_ARROW) {
		this->protocol.send_move_action(MOVE_RIGHT);
	} else if (key_event->keyval == UP_ARROW) {
		this->protocol.send_move_action(EXTEND_ANGLE);
	} else if (key_event->keyval == DOWN_ARROW) {
		this->protocol.send_move_action(REDUCE_ANGLE);
	} else if (key_event->keyval == ENTER) {
		this->protocol.send_move_action(JUMP);
	} else if (key_event->keyval == BACK) {
		this->protocol.send_move_action(ROLLBACK);
	}
	return true;
}

Gtk::ScrolledWindow& Player::getWindow() {
	return this->world.getWindow();
}

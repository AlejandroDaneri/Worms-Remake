#include "server_Protocol.h"
#include "Game.h"
#include "Weapon.h"
#include <string>

ServerProtocol::ServerProtocol(Socket&& socket): Protocol(std::move(socket)){}

ServerProtocol::ServerProtocol(ServerProtocol&& other): Protocol(std::move(other)) {}

ServerProtocol::~ServerProtocol(){}

void ServerProtocol::sendObject(physical_object_ptr& object){
	char buffer[MAX_BUF_LEN];
	buffer[0] = MOVING_OBJECT;

	std::string& type = object->getType();
	if (type == "Worm"){
		this->send_worm(object, buffer);
	} else if (type == "Weapon"){
		this->send_weapon(object, buffer);
	}
}

void ServerProtocol::sendDeadObject(physical_object_ptr& object){
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
	buffer[offset++] = DEAD_OBJECT;

	std::string& type = object->getType();
	if (type == "Worm"){
		buffer[offset++] = WORM_TYPE;
	} else if (type == "Weapon"){
		buffer[offset++] = WEAPON_TYPE;
	}

	uint32_t id = object->getId();
	this->send_int(buffer, offset, id);

	this->send_buffer(buffer, offset);
}

void ServerProtocol::send_worm(physical_object_ptr& object, char* buffer){
	Worm* worm = (Worm*)object.get();
	size_t offset = 1;
	buffer[offset++] = WORM_TYPE;
	int32_t id = worm->getId();

	b2Vec2 position = worm->getPosition();

	char dir = worm->getDir();

	this->send_int(buffer, offset, id);
	this->send_int(buffer, offset, position.x);
	this->send_int(buffer, offset, position.y);
	this->send_int(buffer, offset, worm->getLife());
	buffer[offset++] = dir;
	
	this->send_buffer(buffer, offset);
}

void ServerProtocol::send_weapon(physical_object_ptr& object, char* buffer){
	size_t offset = 1;
	buffer[offset++] = WEAPON_TYPE;
	this->send_int(buffer, offset, object->getId());


	b2Vec2 position = object->getPosition();
	Weapon* weapon = (Weapon*)object.get();
	std::string name = weapon->getName();

	this->send_string(buffer, offset, name);
	
	this->send_int(buffer, offset, position.x);
	this->send_int(buffer, offset, position.y);

	this->send_buffer(buffer, offset);
}

void ServerProtocol::send_start_turn(uint32_t current_worm_id){
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
	buffer[offset++] = START_TURN;

	this->send_int(buffer, offset, current_worm_id);

	this->send_buffer(buffer, offset);
}

void ServerProtocol::receive(Game& game){

	char buffer[MAX_BUF_LEN];
	
	this->receive_buffer(buffer);

	size_t offset = 0;
	char action = buffer[offset++];

	if (action == END_TURN){
		game.endTurn();
	} else if (action == ACTION){
		char worm_action = buffer[offset++];
		if (worm_action == MOVE_ACTION){
			char move = buffer[offset++];
			game.getCurrentWorm().move(move);
		} else if (worm_action == CHANGE_WEAPON_ACTION){
			std::string weapon(this->receive_string(buffer, offset));
			game.getCurrentWorm().changeWeapon(weapon);
		} else if (worm_action == SHOOT_WEAPON){
			int angle = this->receive_int(buffer, offset);
			int power = this->receive_int(buffer, offset);
			int time = this->receive_int(buffer, offset);
			
			game.getCurrentWorm().shoot(angle, power, time);
		} else if(worm_action == SHOOT_SELF_DIRECTED){
			int pos_x = this->receive_int(buffer, offset);
			int pos_y = this->receive_int(buffer, offset);
			game.getCurrentWorm().shoot(b2Vec2(pos_x, pos_y));
		}
	}
}

#include "ServerProtocol.h"
#include "Game.h"
#include "Weapon.h"
#include "Girder.h"
#include "ObjectSizes.h"
#include "Player.h"
#include <string>

ServerProtocol::ServerProtocol(Socket&& socket): Protocol(std::move(socket)){}

ServerProtocol::ServerProtocol(ServerProtocol&& other): Protocol(std::move(other)) {}

ServerProtocol::~ServerProtocol(){}

void ServerProtocol::sendObject(physical_object_ptr& object){
	char buffer[MAX_BUF_LEN];
	buffer[0] = MOVING_OBJECT;

	const std::string& type = object->getType();
	if (type == TYPE_WORM){
		this->send_worm(object, buffer);
	} else if (type == TYPE_WEAPON){
		this->send_weapon(object, buffer);
	}
}

void ServerProtocol::sendDeadObject(physical_object_ptr& object){
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
	buffer[offset++] = DEAD_OBJECT;

	const std::string& type = object->getType();
	if (type == TYPE_WORM){
		buffer[offset++] = WORM_TYPE;
	} else if (type == TYPE_WEAPON){
		buffer[offset++] = WEAPON_TYPE;
	}

	uint32_t id = object->getId();
    this->send_int_buffer(buffer, offset, id);

	this->send_buffer(buffer, offset);
}

void ServerProtocol::send_worm(physical_object_ptr& object, char* buffer){
	Worm* worm = (Worm*)object.get();
	size_t offset = 1;
	buffer[offset++] = WORM_TYPE;
	int32_t id = worm->getId();

	b2Vec2 position = worm->getPosition();

    this->send_int_buffer(buffer, offset, id);
    this->send_int_buffer(buffer, offset, worm->getPlayerId());
    this->send_int_buffer(buffer, offset, position.x * UNIT_TO_SEND);
    this->send_int_buffer(buffer, offset, position.y * UNIT_TO_SEND);
    this->send_int_buffer(buffer, offset, worm->getLife());
	buffer[offset++] = worm->getDir();
	buffer[offset++] = (char)worm->isColliding();
	
	this->send_buffer(buffer, offset);
}

void ServerProtocol::send_weapon(physical_object_ptr& object, char* buffer){
	size_t offset = 1;
	buffer[offset++] = WEAPON_TYPE;
    this->send_int_buffer(buffer, offset, object->getId());


	b2Vec2 position = object->getPosition();
	Weapon* weapon = (Weapon*)object.get();
	std::string name = weapon->getName();

	this->send_string_buffer(buffer, offset, name);

    this->send_int_buffer(buffer, offset, position.x * UNIT_TO_SEND);
    this->send_int_buffer(buffer, offset, position.y * UNIT_TO_SEND);

	this->send_buffer(buffer, offset);
}

void ServerProtocol::send_start_turn(int32_t current_worm_id, int32_t current_player_id){
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
	buffer[offset++] = START_TURN;

    this->send_int_buffer(buffer, offset, current_worm_id);
    this->send_int_buffer(buffer, offset, current_player_id);

	this->send_buffer(buffer, offset);
}

void ServerProtocol::receive(Game& game) {

	char buffer[MAX_BUF_LEN];
	
	this->receive_buffer(buffer);

	size_t offset = 0;
	char action = buffer[offset++];

	if (action == END_TURN) {
		game.endTurn();
	} else if (action == ACTION) {
		char worm_action = buffer[offset++];
		if (worm_action == MOVE_ACTION){
			char move = buffer[offset++];
			game.getCurrentWorm().move(move);
		} else if (worm_action == CHANGE_WEAPON_ACTION) {
		    ////////////////////////////////////////////// Mejorar por algo mas simple//////////////////////////
			std::string weapon(this->receive_string_buffer(buffer, offset));
			game.getCurrentWorm().changeWeapon(weapon);
			/////////////////////////////////////////////////////////////////
			char weapon_buffer[MAX_BUF_LEN];
			size_t aux = 0;
            weapon_buffer[aux++] = CHANGE_WEAPON_ACTION;
			this->send_string_buffer(weapon_buffer, aux, weapon);
			this->send_buffer(weapon_buffer, aux);
			////////////////////////////////////////////////////////////////
		} else if (worm_action == SHOOT_WEAPON) {
			int angle = this->receive_int_buffer(buffer, offset);
			int power = this->receive_int_buffer(buffer, offset);
			int time = this->receive_int_buffer(buffer, offset);
			
			game.getCurrentWorm().shoot(angle, power, time);
		} else if(worm_action == SHOOT_SELF_DIRECTED) {
			int pos_x = this->receive_int_buffer(buffer, offset);
			int pos_y = this->receive_int_buffer(buffer, offset);
			game.getCurrentWorm().shoot(b2Vec2(pos_x, pos_y));
		}
	}
}

void ServerProtocol::sendPlayerId(const Player& player){
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;

    this->send_int_buffer(buffer, offset, player.getId());
	this->send_string_buffer(buffer, offset, player.getName());

	this->send_buffer(buffer, offset);
}

void ServerProtocol::sendGirder(physical_object_ptr& object){
	Girder* girder = (Girder*)object.get();

	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
    this->send_int_buffer(buffer, offset, girder->getSize());

	b2Vec2 position = object->getPosition();
    this->send_int_buffer(buffer, offset, position.x);
    this->send_int_buffer(buffer, offset, position.y);
    this->send_int_buffer(buffer, offset, girder->getRotation());

	this->send_buffer(buffer, offset);
}

void ServerProtocol::sendWeaponAmmo(const std::string& weapon_name, int ammo){
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;

	this->send_string_buffer(buffer, offset, weapon_name);
    this->send_int_buffer(buffer, offset, ammo);

	this->send_buffer(buffer, offset);
}

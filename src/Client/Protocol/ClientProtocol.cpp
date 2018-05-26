#include "ClientProtocol.h"
#include <string>
#include "Player.h"
#include "WeaponList.h"

ClientProtocol::ClientProtocol(Socket&& socket): Protocol(std::move(socket)) {}

ClientProtocol::ClientProtocol(ClientProtocol&& other): Protocol(std::move(other)) {}

ClientProtocol::~ClientProtocol(){}

void ClientProtocol::send_move_action(char action){
	Buffer buffer;
	buffer.buffer[buffer.offset++] = ACTION;
	buffer.buffer[buffer.offset++] = MOVE_ACTION;
	buffer.buffer[buffer.offset++] = action;
	this->send_buffer(buffer);
}

void ClientProtocol::send_change_weapon(const std::string& weapon){
	Buffer buffer;
	buffer.buffer[buffer.offset++] = ACTION;
	buffer.buffer[buffer.offset++] = CHANGE_WEAPON_ACTION;
	this->send_string_buffer(buffer, weapon);
	this->send_buffer(buffer);
}

void ClientProtocol::send_weapon_shoot(int32_t angle, int32_t power, int32_t time){
	Buffer buffer;
	buffer.buffer[buffer.offset++] = ACTION;
	buffer.buffer[buffer.offset++] = SHOOT_WEAPON;
    this->send_int_buffer(buffer, angle);
    this->send_int_buffer(buffer, power);
    this->send_int_buffer(buffer, time);
	this->send_buffer(buffer);
}

void ClientProtocol::send_weapon_self_directed_shoot(const Position& pos) {
	Buffer buffer;
	buffer.buffer[buffer.offset++] = ACTION;
	buffer.buffer[buffer.offset++] = SHOOT_SELF_DIRECTED;

    this->send_int_buffer(buffer, pos.getX());
    this->send_int_buffer(buffer, pos.getY());

	this->send_buffer(buffer);
}

void ClientProtocol::send_end_turn(){
	Buffer buffer;
	buffer.buffer[buffer.offset++] = END_TURN;
	this->send_buffer(buffer);
}

void ClientProtocol::receive(Player& player, ViewsList& viewsList){
	Buffer buffer = std::move(this->receive_buffer());
	char action = buffer.buffer[buffer.offset++];

	if (action == START_TURN){
		int worm_id = this->receive_int_buffer(buffer);
		int player_id = this->receive_int_buffer(buffer);
		player.startTurn(worm_id, player_id);
	} else if (action == CHANGE_WEAPON_ACTION) {
        std::string weapon(this->receive_string_buffer(buffer));
        viewsList.changeWeapon(weapon);
    } else if (action == MOVING_OBJECT) {
		char type = buffer.buffer[buffer.offset++];
		int id = this->receive_int_buffer(buffer);

		if (type == WORM_TYPE){
			int player_id = this->receive_int_buffer(buffer);
			int pos_x = this->receive_int_buffer(buffer);
			int pos_y = this->receive_int_buffer(buffer);
			int life = this->receive_int_buffer(buffer);
			char dir = buffer.buffer[buffer.offset++];
			bool colliding = buffer.buffer[buffer.offset++];
			viewsList.updateWormData(id, player_id, pos_x, pos_y, life, dir, colliding);
		} else if (type == WEAPON_TYPE){
			std::string weapon(this->receive_string_buffer(buffer));

			int pos_x = this->receive_int_buffer(buffer);
			int pos_y = this->receive_int_buffer(buffer);
			viewsList.updateWeaponData(id, weapon, pos_x, pos_y);
		}
	} else if (action == DEAD_OBJECT){
		char type = buffer.buffer[buffer.offset++];
		int id = this->receive_int_buffer(buffer);
		if (type == WORM_TYPE){
			viewsList.removeWorm(id);
		} else if (type == WEAPON_TYPE){
			viewsList.removeWeapon(id);
		}
	}
}

void ClientProtocol::receivePlayers(PlayersList& players_list){
	int quantity = this->receive_length();

	for (int i = 0; i < quantity; i++){
		Buffer buffer = std::move(this->receive_buffer());

		int id = this->receive_int_buffer(buffer);
		std::string name = this->receive_string_buffer(buffer);
		
		players_list.addPlayer(id, name);
	}
}

void ClientProtocol::receiveGirders(ViewsList& viewsList){
	int quantity = this->receive_length();

	for (int i = 0; i < quantity; i++){
		Buffer buffer = std::move(this->receive_buffer());;

		int size = this->receive_int_buffer(buffer);
		int pos_x = this->receive_int_buffer(buffer);
		int pos_y = this->receive_int_buffer(buffer);
		int rotation = this->receive_int_buffer(buffer);
		viewsList.addGirder(size, pos_x, pos_y, rotation);
	}
}

void ClientProtocol::receiveWeaponsAmmo(WeaponList& weapon_list){
	int quantity = this->receive_length();

	for (int i = 0; i < quantity; i++){
		Buffer buffer = std::move(this->receive_buffer());

		std::string name = this->receive_string_buffer(buffer);
		int ammo = this->receive_int_buffer(buffer);
		weapon_list.add(name, ammo);
	}
}

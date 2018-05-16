#include "client_Protocol.h"
#include <string>
#include "client_Player.h"
#include "client_WeaponList.h"

ClientProtocol::ClientProtocol(Socket&& socket): Protocol(std::move(socket)) {}

ClientProtocol::ClientProtocol(ClientProtocol&& other): Protocol(std::move(other)) {}

ClientProtocol::~ClientProtocol(){}

void ClientProtocol::send_move_action(char action){
	printf("Move_action\n");
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
	buffer[offset++] = ACTION;
	buffer[offset++] = MOVE_ACTION;
	buffer[offset++] = action;
	this->send_buffer(buffer, offset);
}

void ClientProtocol::send_change_weapon(const std::string& weapon){
	printf("Weapon\n");
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
	buffer[offset++] = ACTION;
	buffer[offset++] = CHANGE_WEAPON_ACTION;
	this->send_string(buffer, offset, weapon);
	this->send_buffer(buffer, offset);
}

void ClientProtocol::send_weapon_shoot(int32_t angle, int32_t power, int32_t time){
	printf("shoot protocol\n");
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
	buffer[offset++] = ACTION;
	buffer[offset++] = SHOOT_WEAPON;
	this->send_int(buffer, offset, angle);
	this->send_int(buffer, offset, power);
	this->send_int(buffer, offset, time);
	this->send_buffer(buffer, offset);
}

void ClientProtocol::send_weapon_self_directed_shoot(const Position& pos) {
	printf("dirigido\n");
	char buffer[MAX_BUF_LEN];
	size_t offset = 0;
	buffer[offset++] = ACTION;
	buffer[offset++] = SHOOT_SELF_DIRECTED;
	
	this->send_int(buffer, offset, pos.getX());
	this->send_int(buffer, offset, pos.getY());

	this->send_buffer(buffer, offset);
}

void ClientProtocol::send_end_turn(){
	printf("fin turno\n");
	char buffer[MAX_BUF_LEN];
	buffer[0] = END_TURN;
	this->send_buffer(buffer, 1);
}

void ClientProtocol::receive(Player& player, ViewsList& viewsList){
	char buffer[MAX_BUF_LEN];
	this->receive_buffer(buffer);
	size_t offset = 0;
	char action = buffer[offset++];

	if (action == START_TURN){
		int id = this->receive_int(buffer, offset);
		player.startTurn(id);
	} else if (action == MOVING_OBJECT){
		char type = buffer[offset++];
		int id = this->receive_int(buffer, offset);

		if (type == WORM_TYPE){
			int pos_x = this->receive_int(buffer, offset);
			int pos_y = this->receive_int(buffer, offset);
			int life = this->receive_int(buffer, offset);
			char dir = buffer[offset++];
			viewsList.updateWormData(id, pos_x, pos_y, life, dir);
		} else if (type == WEAPON_TYPE){
			std::string weapon(this->receive_string(buffer, offset));

			int pos_x = this->receive_int(buffer, offset);
			int pos_y = this->receive_int(buffer, offset);
			viewsList.updateWeaponData(id, weapon, pos_x, pos_y);
		}
	} else if (action == DEAD_OBJECT){
		char type = buffer[offset++];
		int id = this->receive_int(buffer, offset);
		if (type == WORM_TYPE){
			viewsList.removeWorm(id);
		} else if (type == WEAPON_TYPE){
			viewsList.removeWeapon(id);
		}
	}
}

void ClientProtocol::receiveGirders(ViewsList& viewsList){
	int quantity = this->receive_length();

	for (int i = 0; i < quantity; i++){
		char buffer[MAX_BUF_LEN];
		this->receive_buffer(buffer);
		size_t offset = 0;

		int size = this->receive_int(buffer, offset);
		int pos_x = this->receive_int(buffer, offset);
		int pos_y = this->receive_int(buffer, offset);
		int rotation = this->receive_int(buffer, offset);
		viewsList.addGirder(size, pos_x, pos_y, rotation);
	}
}

void ClientProtocol::receiveWeaponsAmmo(WeaponList& weapon_list){
	int quantity = this->receive_length();

	for (int i = 0; i < quantity; i++){
		char buffer[MAX_BUF_LEN];
		this->receive_buffer(buffer);
		size_t offset = 0;

		std::string name = this->receive_string(buffer, offset);
		int ammo = this->receive_int(buffer, offset);
		weapon_list.add(name, ammo);
	}
}

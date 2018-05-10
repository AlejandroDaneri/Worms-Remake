#include "client_Protocol.h"
#include <string>
#include <cstring>


Protocol::Protocol(Socket&& socket): socket(std::move(socket)){}

Protocol::Protocol(Protocol&& other): socket(std::move(other.socket)){}

Protocol::~Protocol(){}

void Protocol::send_move_action(char action){
	char buffer[MAX_BUF_LEN];
	buffer[0] = ACTION;
	buffer[1] = MOVE_ACTION;
	buffer[2] = action;

	this->send_string(buffer, 3);
}

void Protocol::send_change_weapon(const std::string& weapon){
	char buffer[MAX_BUF_LEN];
	buffer[0] = ACTION;
	buffer[1] = CHANGE_WEAPON_ACTION;
	size_t i = 2;
	for (size_t j = 0; j < weapon.size(); i++, j++){
		buffer[i] = weapon[j];
	}
	buffer[i] = '\0';

	this->send_string(buffer, i + 1);
}

void Protocol::send_weapon_shoot(int32_t angle, int32_t power, int32_t time){
	char buffer[MAX_BUF_LEN];
	buffer[0] = ACTION;
	buffer[1] = SHOOT_WEAPON;

	angle = htonl(angle);
	power = htonl(power);
	time = htonl(time);

	std::memcpy(buffer + 2, &angle, sizeof(angle));
	std::memcpy(buffer + 6, &power, sizeof(power));
	std::memcpy(buffer + 10, &time, sizeof(time));

	this->send_string(buffer, 14);
}

void Protocol::send_weapon_self_directed_shoot(const Position& pos){
	char buffer[MAX_BUF_LEN];
	buffer[0] = ACTION;
	buffer[1] = SHOOT_SELF_DIRECTED;

	int32_t pos_x = htonl((int32_t)pos.getX());
	int32_t pos_y = htonl((int32_t)pos.getY());

	std::memcpy(buffer + 2, &pos_x, sizeof(pos_x));
	std::memcpy(buffer + 6, &pos_y, sizeof(pos_y));

	this->send_string(buffer, 10);
}

void Protocol::send_end_turn(){
	char buffer[MAX_BUF_LEN];
	buffer[0] = END_TURN;

	this->send_string(buffer, 1);
}

void Protocol::send_string(const char* buffer, size_t size){
	uint32_t len_converted = htonl(size);

	this->socket.send_data(&len_converted, sizeof len_converted);
	this->socket.send_data(buffer, size);
}

void Protocol::receive(Player& player, ViewsList& viewsList){
	uint32_t len;
	this->socket.receive(&len, sizeof (uint32_t));
	len = ntohl(len);

	char buffer[MAX_BUF_LEN];
	this->socket.receive(buffer, len);

	char action = buffer[0];

	if (action == START_TURN){
		uint32_t id;
		std::memcpy(&id, buffer + 1, sizeof(id));
		id = ntohl(id);
		player.startTurn(id);
	} else if (action == MOVING_OBJECT){
		char type = buffer[1];
		uint32_t id;
		std::memcpy(&id, buffer + 2, sizeof(id));
		id = ntohl(id);

		if (type == WORM_TYPE){
			int32_t pos_x, pos_y, life;
			std::memcpy(&pos_x, buffer + 6, sizeof(pos_x));
			std::memcpy(&pos_y, buffer + 10, sizeof(pos_y));
			std::memcpy(&life, buffer + 14, sizeof(life));
			char dir = buffer[18];
			pos_x = ntohl(pos_x);
			pos_y = ntohl(pos_y);
			life = ntohl(life);
			viewsList.updateWormData(id, pos_x, pos_y, life, dir);
		} else if (type == WEAPON_TYPE){
			std::string weapon;
			size_t i = 6;
			while (buffer[i] != '\0'){
				weapon += buffer[i];
				i++;
			}

			int32_t pos_x, pos_y;
			std::memcpy(&pos_x, buffer + i + 1, sizeof(pos_x));
			std::memcpy(&pos_y, buffer + i + 5, sizeof(pos_y));
			pos_x = ntohl(pos_x);
			pos_y = ntohl(pos_y);
			viewsList.updateWeaponData(id, weapon, pos_x, pos_y);
		}
	} else if (action == DEAD_OBJECT){
		char type = buffer[1];
		uint32_t id;
		std::memcpy(&id, buffer + 2, sizeof(id));
		id = ntohl(id);
		if (type == WORM_TYPE){
			viewsList.removeWorm(id);
		} else if (type == WEAPON_TYPE){
			viewsList.removeWeapon(id);
		}
	}
}

void Protocol::stop(){
	this->socket.stop();
}

#include "server_Protocol.h"
#include "Game.h"
#include "Weapon.h"
#include <string>
#include <cstring>

Protocol::Protocol(Socket&& socket): socket(std::move(socket)){}

Protocol::Protocol(Protocol&& other): socket(std::move(other.socket)){}

Protocol::~Protocol(){}

void Protocol::sendObject(physical_object_ptr& object){
	char buffer[MAX_BUF_LEN];
	buffer[0] = MOVING_OBJECT;

	std::string& type = object->getType();
	if (type == "Worm"){
		this->send_worm(object, buffer);
	} else if (type == "Weapon"){
		this->send_weapon(object, buffer);
	}
}

void Protocol::sendDeadObject(physical_object_ptr& object){
	char buffer[MAX_BUF_LEN];
	buffer[0] = DEAD_OBJECT;

	std::string& type = object->getType();
	if (type == "Worm"){
		buffer[1] = WORM_TYPE;
	} else if (type == "Weapon"){
		buffer[1] = WEAPON_TYPE;
	}

	uint32_t id = object->getId();
	uint32_t converted = htonl(id);
	std::memcpy(buffer + 2, &converted, sizeof(converted));

	this->send_string(buffer, 6);
}

void Protocol::send_worm(physical_object_ptr& object, char* buffer){
	Worm* worm = (Worm*)object.get();

	buffer[1] = WORM_TYPE;
	uint32_t id = htonl((uint32_t)worm->getId());

	b2Vec2 position = worm->getPosition();

	int32_t pos_x = htonl((int32_t)position.x);
	int32_t pos_y = htonl((int32_t)position.y);
	int32_t life = htonl((int32_t)worm->getLife());
	char dir = worm->getDir();

	std::memcpy(buffer + 2, &id, sizeof(id));
	std::memcpy(buffer + 6, &pos_x, sizeof(pos_x));
	std::memcpy(buffer + 10, &pos_y, sizeof(pos_y));
	std::memcpy(buffer + 14, &life, sizeof(life));
	buffer[18] = dir;
	
	this->send_string(buffer, 19);
}

void Protocol::send_weapon(physical_object_ptr& object, char* buffer){
	buffer[1] = WEAPON_TYPE;
	uint32_t id = htonl((uint32_t)object->getId());
	std::memcpy(buffer + 2, &id, sizeof(id));

	b2Vec2 position = object->getPosition();
	Weapon* weapon = (Weapon*)object.get();
	std::string name = weapon->getName();
	int32_t pos_x = htonl((int32_t)position.x);
	int32_t pos_y = htonl((int32_t)position.y);

	size_t i = 6;
	for (size_t j = 0; j < name.size(); i++, j++){
		buffer[i] = name[j];
	}
	buffer[i] = '\0';
	std::memcpy(buffer + i + 1, &pos_x, sizeof(pos_x));
	std::memcpy(buffer + i + 5, &pos_y, sizeof(pos_y));

	this->send_string(buffer, i + 9);
}

void Protocol::send_string(const char* buffer, size_t size){
	uint32_t len_converted = htonl(size);

	std::lock_guard<std::mutex> lock(this->mutex_send);
	this->socket.send_data(&len_converted, sizeof len_converted);
	this->socket.send_data(buffer, size);
}

void Protocol::send_start_turn(uint32_t current_worm_id){
	char buffer[MAX_BUF_LEN];
	buffer[0] = START_TURN;

	uint32_t id = htonl(current_worm_id);
	std::memcpy(buffer + 1, &id, sizeof(id));

	this->send_string(buffer, 5);
}

void Protocol::receive(Game& game){
	uint32_t len;
	this->socket.receive(&len, sizeof (uint32_t));
	len = ntohl(len);

	char buffer[MAX_BUF_LEN];
	this->socket.receive(buffer, len);

	char action = buffer[0];

	if (action == END_TURN){
		game.endTurn();
	} else if (action == ACTION){
		char worm_action = buffer[1];
		if (worm_action == MOVE_ACTION){
			char move = buffer[2];
			game.getCurrentWorm()->move(move);
		} else if (worm_action == CHANGE_WEAPON_ACTION){
			std::string weapon;
			size_t i = 2;
			while (buffer[i] != '\0'){
				weapon += buffer[i];
				i++;
			}
			game.getCurrentWorm()->changeWeapon(weapon);
		} else if (worm_action == SHOOT_WEAPON){
			int32_t angle, power, time;
			std::memcpy(&angle, buffer + 2, sizeof(angle));
			std::memcpy(&power, buffer + 6, sizeof(power));
			std::memcpy(&time, buffer + 10, sizeof(time));
			angle = ntohl(angle);
			power = ntohl(power);
			time = ntohl(time);
			game.getCurrentWorm()->shoot(angle, power, time);
		} else if(worm_action == SHOOT_SELF_DIRECTED){
			int32_t pos_x, pos_y;
			std::memcpy(&pos_x, buffer + 2, sizeof(pos_x));
			std::memcpy(&pos_y, buffer + 6, sizeof(pos_y));
			pos_x = ntohl(pos_x);
			pos_y = ntohl(pos_y);
			game.getCurrentWorm()->shoot(b2Vec2(pos_x, pos_y));
		}
	}
}

void Protocol::stop(){
	this->socket.stop();
}

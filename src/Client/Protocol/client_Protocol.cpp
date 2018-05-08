#include "client_Protocol.h"
#include <string>
#include <sstream>

Protocol::Protocol(Socket&& socket): socket(std::move(socket)){}

Protocol::Protocol(Protocol&& other): socket(std::move(other.socket)){}

Protocol::~Protocol(){}

void Protocol::send_move_action(char action){
	std::stringstream stream;
	stream << ACTION << MOVE_ACTION << action;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_change_weapon(const std::string& weapon){
	std::stringstream stream;
	stream << ACTION << CHANGE_WEAPON_ACTION << weapon << '\0';

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_weapon_shoot(uint32_t angle, uint32_t power, uint32_t time){
	std::stringstream stream;

	angle = htonl(angle);
	power = htonl(power);
	time = htonl(time);

	stream << ACTION << SHOOT_WEAPON << angle << power << time;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_weapon_self_directed_shoot(const Position& pos){
	std::stringstream stream;

	uint32_t pos_x = htonl((uint32_t)pos.getX());
	uint32_t pos_y = htonl((uint32_t)pos.getY());

	stream << ACTION << SHOOT_SELF_DIRECTED << pos_x << pos_y;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_end_turn(){
	std::stringstream stream;
	stream << END_TURN;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_string(const std::string& string){
	uint32_t len = string.size();
	uint32_t len_converted = htonl(len);

	this->socket.send_data(&len_converted, sizeof len_converted);
	this->socket.send_data(string.c_str(), len);
}

void Protocol::receive(Player& player, ViewsList& viewsList){
	uint32_t len;
	this->socket.receive(&len, sizeof (uint32_t));
	len = ntohl(len);

	char buffer[MAX_BUF_LEN];
	this->socket.receive(buffer, len);
	buffer[len] = '\0';

	std::string received(buffer);
	std::stringstream stream(received);

	char action = stream.get();

	if (action == START_TURN){
		player.startTurn();
	} else if (action == MOVING_OBJECT){
		char type = stream.get();
		uint32_t id;
		stream >> id;
		id = ntohl(id);

		if (type == WORM_TYPE){
			uint32_t pos_x, pos_y, life;
			char dir;
			stream >> pos_x >> pos_y >> life >> dir;
			pos_x = ntohl(pos_x);
			pos_y = ntohl(pos_y);
			life = ntohl(life);
			viewsList.updateWormData(id, pos_x, pos_y, life, dir);
		} else if (type == WEAPON_TYPE){
			std::string weapon;
			char c;
			while ((c = stream.get() != '\0')){
				weapon += c;
			}

			uint32_t pos_x, pos_y;
			stream >> pos_x >> pos_y;
			pos_x = ntohl(pos_x);
			pos_y = ntohl(pos_y);
			viewsList.updateWeaponData(id, weapon, pos_x, pos_y);
		}
	} else if (action == DEAD_OBJECT){
		char type = stream.get();
		uint32_t id;
		stream >> id;
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

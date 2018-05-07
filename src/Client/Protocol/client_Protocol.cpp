#include "client_Protocol.h"
#include <string>
#include <sstream>

Protocol::Protocol(Socket&& socket): socket(std::move(socket)){}

Protocol::Protocol(Protocol&& other): socket(std::move(other.socket)){}

Protocol::~Protocol(){}

void Protocol::send_move_action(char action){
	std::stringstream stream;
	stream << MOVE_ACTION << action;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_change_weapon(const std::string& weapon){
	std::stringstream stream;
	stream << CHANGE_WEAPON_ACTION << weapon << '\0';

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_weapon_shoot(uint32_t angle, uint32_t power, uint32_t time){
	std::stringstream stream;

	angle = htonl(angle);
	power = htonl(power);
	time = htonl(time);

	stream << SHOOT_WEAPON << angle << power << time;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_weapon_self_directed_shoot(const Position& pos){
	std::stringstream stream;

	uint32_t pos_x = htonl((uint32_t)pos.getX());
	uint32_t pos_y = htonl((uint32_t)pos.getY());

	stream << SHOOT_SELF_DIRECTED << pos_x << pos_y;

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

void Protocol::receive(){}

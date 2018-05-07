#include "server_Protocol.h"
#include <string>
#include <stringstream>

Protocol::Protocol(Socket&& socket): socket(std::move(socket)){}

Protocol::~Protocol(){}

void Protocol::sendObject(physical_object_ptr& object){
	std::stringstream stream;
	stream << MOVING_OBJECT;

	std::string& type = object->getType();
	if (type == "Worm"){
		this->send_worm(object, stream);
	} else if (type == "Weapon"){
		this->send_weapon(object, stream);
	}
}

void Protocol::sendDeadObject(physical_object_ptr& object){
	std::stringstream stream;
	stream << DEAD_OBJECT;

	std::string& type = object->getType();
	if (type == "Worm"){
		stream << = WORM_TYPE;
	} else if (type == "Weapon"){
		stream << = WEAPON_TYPE;
	}

	uint32_t id = object->getId();
	uint32_t converted = htonl(id);
	stream << converted;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_worm(physical_object_ptr& object, std::stringstream& stream){
	std::unique_ptr<Worm> worm(std::move(object));

	stream << WORM_TYPE;
	uint32_t id = htonl((uint32_t)worm->getId());

	b2Vec2 position = worm->getPosition();
	uint32_t pos_x = htonl((uint32_t)position.x);
	uint32_t pos_y = htonl((uint32_t)position.y);
	uint32_t life = htonl((uint32_t)worm->getLife());
	dir_t dir = worm->getDir();

	stream << id << pos_x << pos_y << life << dir;
	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_weapon(physical_object_ptr& weapon, std::stringstream& stream){
	stream << WEAPON_TYPE;
	uint32_t id = htonl((uint32_t)weapon->getId());

	b2Vec2 position = weapon->getPosition();
	uint32_t pos_x = htonl((uint32_t)position.x);
	uint32_t pos_y = htonl((uint32_t)position.y);

	stream << id << pos_x << pos_y;
	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_string(const std::string& string){
	uint32_t len = string.size();
	uint32_t len_converted = htonl(len);

	std::lock_guard<std::mutex> lock(this->mutex_send);
	this->socket.send_data(len_converted, sizeof len_converted);
	this->socket.send_data(string.c_str(), len);
}

void Protocol::receive(Game& game);

void Protocol::send_init_turn(int id);
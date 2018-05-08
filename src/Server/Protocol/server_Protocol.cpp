#include "server_Protocol.h"
#include "Game.h"
#include <string>
#include <sstream>

Protocol::Protocol(Socket&& socket): socket(std::move(socket)){}

Protocol::Protocol(Protocol&& other): socket(std::move(other.socket)){}

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
		stream << WORM_TYPE;
	} else if (type == "Weapon"){
		stream << WEAPON_TYPE;
	}

	uint32_t id = object->getId();
	uint32_t converted = htonl(id);
	stream << converted;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::send_worm(physical_object_ptr& object, std::stringstream& stream){
	Worm* worm = (Worm*)object.get();

	stream << WORM_TYPE;
	uint32_t id = htonl((uint32_t)worm->getId());

	b2Vec2 position = worm->getPosition();
	uint32_t pos_x = htonl((uint32_t)position.x);
	uint32_t pos_y = htonl((uint32_t)position.y);
	uint32_t life = htonl((uint32_t)worm->getLife());
	char dir = worm->getDir();

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
	this->socket.send_data(&len_converted, sizeof len_converted);
	this->socket.send_data(string.c_str(), len);
}

void Protocol::send_start_turn(uint32_t current_worm_id){
	std::stringstream stream;
	stream << START_TURN;

	uint32_t id = htonl(current_worm_id);
	stream << id;

	std::string string = stream.str();
	this->send_string(string);
}

void Protocol::receive(Game& game){
	uint32_t len;
	this->socket.receive(&len, sizeof (uint32_t));
	len = ntohl(len);

	char buffer[MAX_BUF_LEN];
	this->socket.receive(buffer, len);
	buffer[len] = '\0';

	std::string received(buffer);
	std::stringstream stream(received);

	char action = stream.get();

	if (action == END_TURN){
		game.endTurn();
	} else if (action == ACTION){
		char worm_action = stream.get();
		if (worm_action == MOVE_ACTION){
			char move = stream.get();
			game.getCurrentWorm()->move(move);
		} else if (worm_action == CHANGE_WEAPON_ACTION){
			std::string weapon;
			char c;
			while ((c = stream.get() != '\0')){
				weapon += c;
			}
			game.getCurrentWorm()->changeWeapon(weapon);
		} else if (worm_action == SHOOT_WEAPON){
			uint32_t angle, power, time;
			stream >> angle >> power >> time;
			angle = ntohl(angle);
			power = ntohl(power);
			time = ntohl(time);
			game.getCurrentWorm()->shoot(angle, power, time);
		} else if(worm_action == SHOOT_SELF_DIRECTED){
			uint32_t pos_x, pos_y;
			stream >> pos_x >> pos_y;
			pos_x = ntohl(pos_x);
			pos_y = ntohl(pos_y);
			game.getCurrentWorm()->shoot(b2Vec2(pos_x, pos_y));
		}
	}
}

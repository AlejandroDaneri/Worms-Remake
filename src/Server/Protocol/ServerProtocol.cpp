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

Buffer ServerProtocol::sendObject(physical_object_ptr& object){
	Buffer buffer;
	buffer.setNext(MOVING_OBJECT);

	const std::string& type = object->getType();
	if (type == TYPE_WORM){
		this->send_worm(object, buffer);
	} else if (type == TYPE_WEAPON){
		this->send_weapon(object, buffer);
	}
	return std::move(buffer);
}

Buffer ServerProtocol::sendDeadObject(physical_object_ptr& object){
	Buffer buffer;
	buffer.setNext(DEAD_OBJECT);

	const std::string& type = object->getType();
	if (type == TYPE_WORM){
		buffer.setNext(WORM_TYPE);
	} else if (type == TYPE_WEAPON){
		buffer.setNext(WEAPON_TYPE);
	}

	uint32_t id = object->getId();
    this->send_int_buffer(buffer, id);

	return std::move(buffer);
}

void ServerProtocol::send_worm(physical_object_ptr& object, Buffer& buffer){
	Worm* worm = (Worm*)object.get();
	buffer.setNext(WORM_TYPE);
	int32_t id = worm->getId();

	b2Vec2 position = worm->getPosition();

    this->send_int_buffer(buffer, id);
    this->send_int_buffer(buffer, worm->getPlayerId());
    this->send_int_buffer(buffer, position.x * UNIT_TO_SEND);
    this->send_int_buffer(buffer, position.y * UNIT_TO_SEND);
    this->send_int_buffer(buffer, worm->getLife());
	buffer.setNext(worm->getDir());
	buffer.setNext(worm->isColliding());
}

void ServerProtocol::send_weapon(physical_object_ptr& object, Buffer& buffer){
	buffer.setNext(WEAPON_TYPE);
    this->send_int_buffer(buffer, object->getId());


	b2Vec2 position = object->getPosition();
	Weapon* weapon = (Weapon*)object.get();
	std::string name = weapon->getName();

	this->send_string_buffer(buffer, name);

    this->send_int_buffer(buffer, position.x * UNIT_TO_SEND);
    this->send_int_buffer(buffer, position.y * UNIT_TO_SEND);
}

void ServerProtocol::send_start_turn(int32_t current_worm_id, int32_t current_player_id){
	Buffer buffer;
	buffer.setNext(START_TURN);

    this->send_int_buffer(buffer, current_worm_id);
    this->send_int_buffer(buffer, current_player_id);

	this->send_buffer(buffer);
}

void ServerProtocol::receive(Game& game) {

	Buffer buffer = std::move(this->receive_buffer());

	char action = buffer.getNext();

	if (action == END_TURN) {
		game.endTurn();
	} else if (action == ACTION) {
		char worm_action = buffer.getNext();
		if (worm_action == MOVE_ACTION){
			char move = buffer.getNext();
			game.getCurrentWorm().move(move);
		} else if (worm_action == CHANGE_WEAPON_ACTION) {
			std::string weapon(this->receive_string_buffer(buffer));
			game.weaponChanged(weapon);
		} else if(worm_action == MOVE_SCOPE) {
            int32_t angle = this->receive_int_buffer(buffer);
			game.updateScope(angle);
		} else if (worm_action == SHOOT_WEAPON) {
			int angle = this->receive_int_buffer(buffer);
			int power = this->receive_int_buffer(buffer);
			int time = this->receive_int_buffer(buffer);
			game.getCurrentWorm().shoot(angle, power, time);
		} else if(worm_action == SHOOT_SELF_DIRECTED) {
			int pos_x = this->receive_int_buffer(buffer);
			int pos_y = this->receive_int_buffer(buffer);
			game.getCurrentWorm().shoot(b2Vec2(pos_x, pos_y));
		}
	}
}

void ServerProtocol::sendPlayerId(const Player& player){
	Buffer buffer;

    this->send_int_buffer(buffer, player.getId());
	this->send_string_buffer(buffer, player.getName());

	this->send_buffer(buffer);
}

void ServerProtocol::sendGirder(physical_object_ptr& object){
	Girder* girder = (Girder*)object.get();

	Buffer buffer;
    this->send_int_buffer(buffer, girder->getSize());

	b2Vec2 position = object->getPosition();
    this->send_int_buffer(buffer, position.x);
    this->send_int_buffer(buffer, position.y);
    this->send_int_buffer(buffer, girder->getRotation());

	this->send_buffer(buffer);
}

void ServerProtocol::sendWeaponAmmo(const std::string& weapon_name, int ammo){
	Buffer buffer;

	this->send_string_buffer(buffer, weapon_name);
    this->send_int_buffer(buffer, ammo);

	this->send_buffer(buffer);
}

void ServerProtocol::send_weapon_changed(const std::string& weapon){
	Buffer buffer;

	buffer.setNext(CHANGE_WEAPON_ACTION);
	this->send_string_buffer(buffer, weapon);

	this->send_buffer(buffer);
}

void ServerProtocol::sendUpdateScope(int angle) {
    Buffer buffer;

    buffer.setNext(MOVE_SCOPE);
    this->send_int_buffer(buffer, angle);

    this->send_buffer(buffer);
}

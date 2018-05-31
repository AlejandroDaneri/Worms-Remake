#include "ServerProtocol.h"
#include "Game.h"
#include "Weapon.h"
#include "Girder.h"
#include "ObjectSizes.h"
#include "Player.h"
#include "DataSender.h"
#include <string>

ServerProtocol::ServerProtocol(Socket&& socket): Protocol(std::move(socket)){}

ServerProtocol::ServerProtocol(ServerProtocol&& other): Protocol(std::move(other)) {}

ServerProtocol::~ServerProtocol(){}

Buffer ServerProtocol::sendObject(physical_object_ptr& object){
	Buffer buffer;
	buffer.setNext(MOVING_OBJECT);

	const std::string& type = object->getType();
	if (type == TYPE_WORM){
		ServerProtocol::send_worm(object, buffer);
	} else if (type == TYPE_WEAPON){
		ServerProtocol::send_weapon(object, buffer);
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
	ServerProtocol::sendIntBuffer(buffer, id);

	return std::move(buffer);
}

void ServerProtocol::send_worm(physical_object_ptr& object, Buffer& buffer){
	Worm* worm = (Worm*)object.get();
	buffer.setNext(WORM_TYPE);
	int32_t id = worm->getId();

	b2Vec2 position = worm->getPosition();

	ServerProtocol::sendIntBuffer(buffer, id);
	ServerProtocol::sendIntBuffer(buffer, worm->getPlayerId());
	ServerProtocol::sendIntBuffer(buffer, position.x * UNIT_TO_SEND);
	ServerProtocol::sendIntBuffer(buffer, position.y * UNIT_TO_SEND);
	ServerProtocol::sendIntBuffer(buffer, worm->getLife());
	buffer.setNext(worm->getDir());
	buffer.setNext(worm->isColliding());
}

void ServerProtocol::send_weapon(physical_object_ptr& object, Buffer& buffer){
	buffer.setNext(WEAPON_TYPE);
	ServerProtocol::sendIntBuffer(buffer, object->getId());


	b2Vec2 position = object->getPosition();
	Weapon* weapon = (Weapon*)object.get();
	std::string name = weapon->getName();

	ServerProtocol::sendStringBuffer(buffer, name);
	ServerProtocol::sendIntBuffer(buffer, position.x * UNIT_TO_SEND);
	ServerProtocol::sendIntBuffer(buffer, position.y * UNIT_TO_SEND);
}

Buffer ServerProtocol::sendStartGame(){
	Buffer buffer;
	buffer.setNext(START_GAME_ACTION);
	return buffer;
}

Buffer ServerProtocol::sendEndTurn(){
	Buffer buffer;
	buffer.setNext(END_TURN);
	return buffer;
}

Buffer ServerProtocol::send_start_turn(int32_t current_worm_id, int32_t current_player_id, float wind){
	Buffer buffer;
	buffer.setNext(START_TURN);

	ServerProtocol::sendIntBuffer(buffer, current_worm_id);
	ServerProtocol::sendIntBuffer(buffer, current_player_id);
	ServerProtocol::sendIntBuffer(buffer, wind * UNIT_TO_SEND);

    return buffer;
}

void ServerProtocol::receive(Game& game, DataSender& data_sender) {

	Buffer buffer = std::move(this->receiveBuffer());

	char action = buffer.getNext();

	if (action == END_TURN) {
		game.endTurn();
	} else if (action == ACTION) {
		char worm_action = buffer.getNext();
		if (worm_action == MOVE_ACTION){
			char move = buffer.getNext();
			data_sender.sendMoveAction(move);
			game.getCurrentWorm().move(move);
		} else if (worm_action == CHANGE_WEAPON_ACTION) {
			std::string weapon(this->receiveStringBuffer(buffer));
			data_sender.send_weapon_changed(weapon);
			game.getCurrentWorm().changeWeapon(weapon);
		} else if(worm_action == MOVE_SCOPE) {
            int32_t angle = this->receiveIntBuffer(buffer);
			data_sender.sendUpdateScope(angle);
		} else if (worm_action == SHOOT_WEAPON) {
			int angle = this->receiveIntBuffer(buffer);
			int power = this->receiveIntBuffer(buffer);
			int time = this->receiveIntBuffer(buffer);
			data_sender.sendWeaponShot(game.getCurrentWorm().getCurrentWeapon());
			game.getCurrentWorm().shoot(angle, power, time);
		} else if(worm_action == SHOOT_SELF_DIRECTED) {
			int pos_x = this->receiveIntBuffer(buffer) / UNIT_TO_SEND;
			int pos_y = this->receiveIntBuffer(buffer) / UNIT_TO_SEND;
			data_sender.sendWeaponShot(game.getCurrentWorm().getCurrentWeapon());
			game.getCurrentWorm().shoot(b2Vec2(pos_x, pos_y));
		}
	}
}

Buffer ServerProtocol::sendBackgroundImage(const std::string& image){
	Buffer buffer;
	ServerProtocol::sendStringBuffer(buffer, image);
	return buffer;
}

Buffer ServerProtocol::sendPlayerId(const Player& player){
	Buffer buffer;
	ServerProtocol::sendIntBuffer(buffer, player.getId());
	ServerProtocol::sendStringBuffer(buffer, player.getName());
	return buffer;
}

Buffer ServerProtocol::sendGirder(physical_object_ptr& object){
	Girder* girder = (Girder*)object.get();

	Buffer buffer;
	ServerProtocol::sendIntBuffer(buffer, girder->getSize());

	b2Vec2 position = object->getPosition();
	ServerProtocol::sendIntBuffer(buffer, position.x * UNIT_TO_SEND);
	ServerProtocol::sendIntBuffer(buffer, position.y * UNIT_TO_SEND);
	ServerProtocol::sendIntBuffer(buffer, girder->getRotation());
	return buffer;
}

Buffer ServerProtocol::sendWeaponAmmo(const std::string& weapon_name, int ammo){
	Buffer buffer;
	ServerProtocol::sendStringBuffer(buffer, weapon_name);
	ServerProtocol::sendIntBuffer(buffer, ammo);
	return buffer;
}

Buffer ServerProtocol::send_weapon_changed(const std::string& weapon){
	Buffer buffer;
	buffer.setNext(CHANGE_WEAPON_ACTION);
	ServerProtocol::sendStringBuffer(buffer, weapon);
    return buffer;
}

Buffer ServerProtocol::send_weapon_shot(const std::string& weapon){
	Buffer buffer;
	buffer.setNext(SHOOT_WEAPON_ACTION);
	ServerProtocol::sendStringBuffer(buffer, weapon);
    return buffer;
}

Buffer ServerProtocol::sendMoveAction(char action){
	Buffer buffer;
	buffer.setNext(MOVE_ACTION);
	buffer.setNext(action);
    return buffer;
}

Buffer ServerProtocol::sendUpdateScope(int angle) {
    Buffer buffer;
    buffer.setNext(MOVE_SCOPE);
	ServerProtocol::sendIntBuffer(buffer, angle);
    return buffer;
}

Buffer ServerProtocol::sendEndGame(const std::string& winner){
	Buffer buffer;
    buffer.setNext(END_GAME);
	ServerProtocol::sendStringBuffer(buffer, winner);
    return buffer;
}

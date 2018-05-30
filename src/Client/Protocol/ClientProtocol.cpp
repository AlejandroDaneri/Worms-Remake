#include "ClientProtocol.h"
#include <string>
#include "Player.h"
#include "WeaponList.h"
#include "ObjectSizes.h"

ClientProtocol::ClientProtocol(Socket&& socket): Protocol(std::move(socket)) {}

ClientProtocol::ClientProtocol(ClientProtocol&& other): Protocol(std::move(other)) {}

ClientProtocol::~ClientProtocol(){}

void ClientProtocol::sendMoveAction(char action){
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(MOVE_ACTION);
	buffer.setNext(action);
    this->sendBuffer(buffer);
}

void ClientProtocol::sendChangeWeapon(const std::string &weapon){
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(CHANGE_WEAPON_ACTION);
    this->sendStringBuffer(buffer, weapon);
    this->sendBuffer(buffer);
}

void ClientProtocol::sendWeaponShoot(int32_t angle, int32_t power, int32_t time){
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(SHOOT_WEAPON);
    this->sendIntBuffer(buffer, angle);
    this->sendIntBuffer(buffer, power);
    this->sendIntBuffer(buffer, time);
    this->sendBuffer(buffer);
}

void ClientProtocol::sendWeaponSelfDirectedShoot(const Position &pos) {
	Buffer buffer;
	buffer.setNext(ACTION);
	buffer.setNext(SHOOT_SELF_DIRECTED);

    this->sendIntBuffer(buffer, pos.getX());
    this->sendIntBuffer(buffer, pos.getY());

    this->sendBuffer(buffer);
}

void ClientProtocol::updateScope(int angle) {
    Buffer buffer;
    buffer.setNext(ACTION);
    buffer.setNext(MOVE_SCOPE);

    this->sendIntBuffer(buffer, angle);

    this->sendBuffer(buffer);
}

void ClientProtocol::sendEndTurn(){
	Buffer buffer;
	buffer.setNext(END_TURN);
    this->sendBuffer(buffer);
}

void ClientProtocol::receive(Player& player){
	Buffer buffer = std::move(this->receiveBuffer());
	char action = buffer.getNext();

	if (action == START_TURN){
		int worm_id = this->receiveIntBuffer(buffer);
		int player_id = this->receiveIntBuffer(buffer);
		float wind = this->receiveIntBuffer(buffer) / UNIT_TO_SEND;
		player.startTurn(worm_id, player_id, wind);
	} else if (action == END_GAME){
		std::string winner = this->receiveStringBuffer(buffer);
		player.endGame(winner);
	} else if (action == CHANGE_WEAPON_ACTION) {
        std::string weapon(this->receiveStringBuffer(buffer));
        player.getViewsList().removeScopeVisibility();
        player.getViewsList().changeWeapon(weapon);
    } else if (action == MOVE_SCOPE) {
	    int angle = this->receiveIntBuffer(buffer);
	    player.getViewsList().updateScope(angle);
	} else if (action == SHOOT_WEAPON_ACTION) {
	    std::string weapon(this->receiveStringBuffer(buffer));
	    player.getViewsList().removeScopeVisibility();
	    player.getMusicPlayer().playWeaponShotSound(weapon);
	} else if (action == MOVING_OBJECT) {
		char type = buffer.getNext();
		int id = this->receiveIntBuffer(buffer);

		if (type == WORM_TYPE){
			int player_id = this->receiveIntBuffer(buffer);
			int pos_x = this->receiveIntBuffer(buffer);
			int pos_y = this->receiveIntBuffer(buffer);
			int life = this->receiveIntBuffer(buffer);
			char dir = buffer.getNext();
			bool colliding = buffer.getNext();
			player.getViewsList().updateWormData(id, player_id, pos_x, pos_y, life, dir, colliding);
			player.getViewsList().removeScopeVisibility();
		} else if (type == WEAPON_TYPE){
			std::string weapon(this->receiveStringBuffer(buffer));

			int pos_x = this->receiveIntBuffer(buffer);
			int pos_y = this->receiveIntBuffer(buffer);
			player.getViewsList().updateWeaponData(id, weapon, pos_x, pos_y);
		}
	} else if (action == DEAD_OBJECT){
		char type = buffer.getNext();
		int id = this->receiveIntBuffer(buffer);
		if (type == WORM_TYPE){
			player.getViewsList().removeWorm(id);
		} else if (type == WEAPON_TYPE){
			player.getViewsList().removeWeapon(id);
		}
	}
}

void ClientProtocol::receiveStartGame(){
	Buffer buffer = std::move(this->receiveBuffer());
}

void ClientProtocol::receivePlayers(PlayersList& players_list){
	Buffer buffer = std::move(this->receiveBuffer());
	int quantity = this->receiveIntBuffer(buffer);

	for (int i = 0; i < quantity; i++){
		Buffer buffer = std::move(this->receiveBuffer());

		int id = this->receiveIntBuffer(buffer);
		std::string name = this->receiveStringBuffer(buffer);
		
		players_list.addPlayer(id, name);
	}
}

void ClientProtocol::receiveGirders(ViewsList& viewsList){
	Buffer buffer = std::move(this->receiveBuffer());
	int quantity = this->receiveIntBuffer(buffer);

	for (int i = 0; i < quantity; i++){
		Buffer buffer = std::move(this->receiveBuffer());;

		int size = this->receiveIntBuffer(buffer);
		int pos_x = this->receiveIntBuffer(buffer);
		int pos_y = this->receiveIntBuffer(buffer);
		int rotation = this->receiveIntBuffer(buffer);
		viewsList.addGirder(size, pos_x, pos_y, rotation);
	}
}

void ClientProtocol::receiveWeaponsAmmo(WeaponList& weapon_list){
	Buffer buffer = std::move(this->receiveBuffer());
	int quantity = this->receiveIntBuffer(buffer);

	for (int i = 0; i < quantity; i++){
		Buffer buffer = std::move(this->receiveBuffer());

		std::string name = this->receiveStringBuffer(buffer);
		int ammo = this->receiveIntBuffer(buffer);
		weapon_list.add(name, ammo);
	}
}

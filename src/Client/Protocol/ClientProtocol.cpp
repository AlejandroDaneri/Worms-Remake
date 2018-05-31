#include "ClientProtocol.h"
#include <string>
#include <iostream>
#include "Player.h"
#include "WeaponList.h"
#include "ObjectSizes.h"

ClientProtocol::ClientProtocol(Socket&& socket, Gtk::Window& window): Protocol(std::move(socket)), window(window){}

ClientProtocol::ClientProtocol(ClientProtocol&& other): Protocol(std::move(other)), window(other.window) {}

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

    this->sendIntBuffer(buffer, pos.getX() * UNIT_TO_SEND);
    this->sendIntBuffer(buffer, pos.getY() * UNIT_TO_SEND);

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

void ClientProtocol::sendBuffer(Buffer &buffer){
	try{
		Protocol::sendBuffer(buffer);
	} catch (const std::exception& e){
		std::cerr << "Ocurrio un error: " << e.what() << std::endl;
		this->window.close();
	}
}

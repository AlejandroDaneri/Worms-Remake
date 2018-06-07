#include "PlayerDataReceiver.h"

PlayerDataReceiver::PlayerDataReceiver(Player& player, DataSender& data_sender):
	player(player), data_sender(data_sender), is_my_turn(false){}

PlayerDataReceiver::~PlayerDataReceiver(){}

void PlayerDataReceiver::run(){
	try{
		while (this->running){
			Buffer data = this->player.getProtocol().receiveBuffer();
			std::lock_guard<std::mutex> lock(this->mutex);
			if (this->is_my_turn){
				this->analizeReceivedData(data);
			}
		}
	} catch (const std::exception& e){
		this->player.disconnect();
	}
}

void PlayerDataReceiver::beginTurn(){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->is_my_turn = true;
}

void PlayerDataReceiver::endTurn(){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->is_my_turn = false;
}

void PlayerDataReceiver::analizeReceivedData(Buffer& buffer){
	char action = buffer.getNext();

	if (action == ACTION) {
		char worm_action = buffer.getNext();
		if (worm_action == MOVE_ACTION){
			char move = buffer.getNext();
			if (this->player.getCurrentWorm().move(move)){
				this->data_sender.sendMoveAction(move);
			}
		} else if (worm_action == CHANGE_WEAPON_ACTION) {
			std::string weapon(ServerProtocol::receiveStringBuffer(buffer));
			this->data_sender.sendWeaponChanged(weapon);
			this->player.changeWeapon(weapon);
		} else if(worm_action == MOVE_SCOPE) {
            int32_t angle = ServerProtocol::receiveIntBuffer(buffer);
			this->data_sender.sendUpdateScope(angle);
		} else if (worm_action == SHOOT_WEAPON) {
			int angle = ServerProtocol::receiveIntBuffer(buffer);
			int power = ServerProtocol::receiveIntBuffer(buffer);
			int time = ServerProtocol::receiveIntBuffer(buffer);
			this->data_sender.sendWeaponShot(this->player.getCurrentWorm().getCurrentWeapon());
			this->player.getCurrentWorm().shoot(angle, power, time);
		} else if(worm_action == SHOOT_SELF_DIRECTED) {
			int pos_x = ServerProtocol::receiveIntBuffer(buffer) / UNIT_TO_SEND;
			int pos_y = ServerProtocol::receiveIntBuffer(buffer) / UNIT_TO_SEND;
			this->data_sender.sendWeaponShot(this->player.getCurrentWorm().getCurrentWeapon());
			this->player.getCurrentWorm().shoot(b2Vec2(pos_x, pos_y));
		}
	}
}
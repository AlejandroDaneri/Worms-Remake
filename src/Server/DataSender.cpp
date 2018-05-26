#include "DataSender.h"

DataSender::DataSender(World& world, std::vector<Player>& players): 
	objects(world.getObjectsList()), girders(world.getGirdersList()), 
	players(players), mutex(world.getMutex()){}

DataSender::~DataSender(){}

void DataSender::run(){
	while(this->running){
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::lock_guard<std::mutex> lock(this->mutex);
		this->active = false;
		auto it = this->objects.begin();

		while(it != this->objects.end()){
			if ((*it)->isDead()){
				for (size_t i = 0; i < this->players.size(); i++){
					try{
						if (this->players[i].isConnected()){
							this->players[i].getProtocol().sendDeadObject(*it);
						}
					} catch(const SocketException& e){
						this->players[i].disconnect();
					}
				}
				it = this->objects.erase(it);
				continue;
			}

			if ((*it)->isMoving()){
				for (size_t i = 0; i < this->players.size(); i++){
					try{
						if (this->players[i].isConnected()){
							this->players[i].getProtocol().sendObject(*it);
						}
					} catch(const SocketException& e){
						this->players[i].disconnect();
					}
					this->active = true;
				}
			}
			++it;
		}
	}
}

void DataSender::send_start_turn(int worm_id, int player_id){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		try{
			player->getProtocol().send_start_turn(worm_id, player_id);
		} catch(const SocketException& e){}
	}
}

void DataSender::send_players_id(){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		try{
			player->getProtocol().send_length(this->players.size());
			for (auto it = this->players.begin(); it != this->players.end(); ++it){
				player->getProtocol().sendPlayerId(*it);
			}
		} catch(const SocketException& e){}
	}
}

void DataSender::sendGirders(){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		try{
			player->getProtocol().send_length(this->girders.size());
			for (auto it = this->girders.begin(); it != this->girders.end(); ++it){
				player->getProtocol().sendGirder(*it);
			}
		} catch(const SocketException& e){}
	}
}

void DataSender::sendWeaponsAmmo(std::map<std::string, int>& weapons){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		try{
			player->getProtocol().send_length(weapons.size());
			for (auto it = weapons.begin(); it != weapons.end(); ++it){
				player->getProtocol().sendWeaponAmmo(it->first, it->second);
			}
		} catch(const SocketException& e){}
	}
}

void DataSender::send_weapon_changed(const std::string& weapon){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		try{
			player->getProtocol().send_weapon_changed(weapon);
		} catch(const SocketException& e){}
	}
}

bool DataSender::isActive(){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->active;
}

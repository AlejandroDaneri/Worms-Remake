#include "DataSender.h"

DataSender::DataSender(World& world, std::vector<Player>& players): 
	objects(world.getObjectsList()), girders(world.getGirdersList()), 
	players(players), mutex(world.getMutex()){}

DataSender::~DataSender(){}

void DataSender::run(){
	while(this->running){
		std::lock_guard<std::mutex> lock(this->mutex);///////////////////////////////ver poner ahi o adentro del otro while
		this->active = false;
		auto it = this->objects.begin();

		while(it != this->objects.end()){
			if ((*it)->isDead()){
				for (size_t i = 0; i < this->players.size(); i++){
					this->players[i].getProtocol().sendDeadObject(*it);
				}
				it = this->objects.erase(it);
				continue;
			}

			if ((*it)->isMoving()){
				for (size_t i = 0; i < this->players.size(); i++){
					this->players[i].getProtocol().sendObject(*it);
					this->active = true;
				}
			}
			++it;
		}
	}
}

void DataSender::sendGirders(){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		player->getProtocol().send_length(this->girders.size());
		for (auto it = this->girders.begin(); it != this->girders.end(); ++it){
			player->getProtocol().sendGirder(*it);
		}
	}
}

void DataSender::sendWeaponsAmmo(std::map<std::string, int>& weapons){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		player->getProtocol().send_length(weapons.size());
		for (auto it = weapons.begin(); it != weapons.end(); ++it){
			player->getProtocol().sendWeaponAmmo(it->first, it->second);
		}
	}
}

bool DataSender::isActive(){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->active;
}

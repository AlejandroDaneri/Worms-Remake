#include "DataSender.h"

DataSender::DataSender(World& world, std::vector<Player>& players): 
	objects(world.getObjectsList()), girders(world.getGirdersList()), 
	players(players), mutex(world.getMutex()), active(false){

		for (size_t i = 0; i < this->players.size(); i++){
			std::unique_ptr<PlayerDataSender> sender(new PlayerDataSender(this->players[i]));
			this->players_data_senders.push_back(std::move(sender));
			this->players_data_senders[i]->start();
		}
	}

DataSender::~DataSender(){
	for (size_t i = 0; i < this->players.size(); i++){
		this->players_data_senders[i]->stop();
		this->players_data_senders[i]->notify();
		this->players_data_senders[i]->join();
	}
}

void DataSender::run(){
	while(this->running){
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::lock_guard<std::mutex> lock(this->mutex);
		this->active = false;
		auto it = this->objects.begin();

		while(it != this->objects.end()){
			if ((*it)->isDead()){
				Buffer data = this->players[0].getProtocol().sendDeadObject(*it);

				for (size_t i = 0; i < this->players.size(); i++){
					if (this->players[i].isConnected()){
						this->players_data_senders[i]->sendData(data);
					}
				}
				it = this->objects.erase(it);
				continue;
			}

			if ((*it)->isMoving()){
				Buffer data = this->players[0].getProtocol().sendObject(*it);
				for (size_t i = 0; i < this->players.size(); i++){
					if (this->players[i].isConnected()){
						this->players_data_senders[i]->sendData(data);
					}
					this->active = true;
				}
			}
			++it;
		}

		for (size_t i = 0; i < this->players.size(); i++){
			if (this->players[i].isConnected()){
				this->players_data_senders[i]->notify();
			}
		}
	}
}

void DataSender::send_start_game(){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		try{
			player->getProtocol().sendChar(START_GAME_ACTION);
		} catch(const SocketException& e){}
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
            player->getProtocol().sendLength(this->players.size());
			for (auto it = this->players.begin(); it != this->players.end(); ++it){
				player->getProtocol().sendPlayerId(*it);
			}
		} catch(const SocketException& e){}
	}
}

void DataSender::sendGirders(){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		try{
            player->getProtocol().sendLength(this->girders.size());
			for (auto it = this->girders.begin(); it != this->girders.end(); ++it){
				player->getProtocol().sendGirder(*it);
			}
		} catch(const SocketException& e){}
	}
}

void DataSender::sendWeaponsAmmo(std::map<std::string, int>& weapons){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
		try{
            player->getProtocol().sendLength(weapons.size());
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

void DataSender::sendUpdateScope(int angle) {
    for (auto player = this->players.begin(); player != this->players.end(); ++player){
        try{
            player->getProtocol().sendUpdateScope(angle);
        } catch(const SocketException& e){}
    }
}

bool DataSender::isActive(){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->active;
}

void DataSender::sendEndGame(const std::string& winner){
	for (auto player = this->players.begin(); player != this->players.end(); ++player){
        try{
            player->getProtocol().sendEndGame(winner);
        } catch(const SocketException& e){}
    }
}

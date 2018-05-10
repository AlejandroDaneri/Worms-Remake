#include "DataSender.h"

DataSender::DataSender(World& world, std::vector<Player>& players): 
	objects(world.getObjectsList()), players(players), mutex(world.getMutex()){}

DataSender::~DataSender(){}

void DataSender::run(){
	while(this->running){
		std::lock_guard<std::mutex> lock(this->mutex);///////////////////////////////ver poner ahi o adentro del otro while
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
				}
			}
			++it;
		}
	}
}

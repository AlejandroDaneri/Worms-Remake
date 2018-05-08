#include "DataSender.h"

DataSender::DataSender(World& world, Protocol& protocol): 
	objects(world.getObjectsList()), protocol(protocol){}

DataSender::~DataSender(){}

void DataSender::run(){
	while(this->running){
		auto it = this->objects.begin();

		while(it != this->objects.end()){
			if ((*it)->isDead()){
				this->protocol.sendDeadObject(*it);
				it = this->objects.erase(it);
				continue;
			}

			if ((*it)->isMoving()){
				this->protocol.sendObject(*it);
			}
			++it;
		}
	}
}

void DataSender::stop(){
	this->protocol.stop();
	Thread::stop();
}
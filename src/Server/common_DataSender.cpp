#include "DataSender.h"

#include "Position.h"

DataSender::DataSender(World& world, ViewsList& views): objects(world.getObjectsList()),
	views(views){}///////////////////////////////////////////////////////////////////////////////////////Eliminar ViewsList& views

DataSender::~DataSender(){}

void DataSender::run(){
	while(this->running){
		auto it = this->objects.begin();

		while(it != this->objects.end()){
			if ((*it)->isDead()){
				//do something////////////////////////////////////////////Enviar por socket
				it = this->objects.erase(it);
				continue;
			}

			if ((*it)->isMoving()){
				////////////////////////////////////////////Enviar por socket
				b2Vec2 pos = (*it)->getPosition();
				Position position(pos.x, pos.y);
				this->views.getWorm((*it)->getId()).updateData(100, 0, position);
			}

			++it;
		}
	}

}
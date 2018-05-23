#include "DataReceiver.h"
#include "Player.h"

DataReceiver::DataReceiver(ViewsList& views, Player& player, ClientProtocol& protocol): 
	views(views), player(player), protocol(protocol){}

DataReceiver::~DataReceiver(){}

void DataReceiver::run(){
	while(this->running){
		try{
			this->protocol.receive(this->player, this->views);
		} catch (const std::exception& e){
			if (this->running){
				throw e;
			}
		}
	}
}

void DataReceiver::stop(){
	Thread::stop();
	this->protocol.stop();
}

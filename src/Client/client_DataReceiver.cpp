#include "DataReceiver.h"

DataReceiver::DataReceiver(ViewsList& views, Player& player, Protocol& protocol): 
	views(views), player(player), protocol(protocol){}

DataReceiver::~DataReceiver(){}

void DataReceiver::run(){
	while(this->running){
		this->protocol.receive(this->player, this->views);
	}
}

void DataReceiver::stop(){
	this->protocol.stop();
	Thread::stop();
}
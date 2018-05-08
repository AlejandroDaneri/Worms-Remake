#include "DataReceiver.h"

DataReceiver::DataReceiver(ViewsList& views, Player& player, Protocol& protocol): 
	views(views), player(player), protocol(protocol){}

DataReceiver::~DataReceiver(){}

void DataReceiver::run(){
	this->protocol.receive(this->player, this->views);
}
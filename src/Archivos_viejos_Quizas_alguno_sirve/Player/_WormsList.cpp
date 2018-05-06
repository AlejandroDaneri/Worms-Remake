#include "WormsList.h"

WormsList::WormsList(std::vector<Worm>&& worms): list(std::move(worms)), current(0){}

WormsList::~WormsList(){}

Worm& WormsList::getCurrentWorm(){
	return this->list.at(this->current);
}

void WormsList::changeWorm(){
	this->current ++;
	if (this->current >= this->list.size()){
		this->current = 0;
	}
}

WormsList::WormsList(WormsList&& other): list(std::move(other.list)), current(other.current){}
#include "WormsList.h"

WormsList::WormsList(): current(0){}

WormsList::~WormsList(){}

worm_ptr WormsList::getCurrentWorm(){
	Worm* worm = (Worm*)this->list.at(this->current).get();
	std::shared_ptr<Worm> ptr(worm);
	return ptr;
}

void WormsList::begin_turn(){
	++ this->current;
	if (this->current >= this->list.size()){
		this->current = 0;
	}
}

void WormsList::add(physical_object_ptr worm){
	this->list.push_back(worm);
}

WormsList::WormsList(WormsList&& other): list(std::move(other.list)), current(other.current){}
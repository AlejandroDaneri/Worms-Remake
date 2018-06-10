#include "WormsList.h"

WormsList::WormsList(): current(0){}

WormsList::~WormsList(){}

Worm& WormsList::getCurrentWorm(){
	Worm* worm = (Worm*)this->list[this->current].get();
	return *worm;
}

void WormsList::beginTurn(){
	do {
		this->current++;
		if (this->current >= this->list.size()){
			this->current = 0;
		}
	} while (this->getCurrentWorm().isDead());
	this->getCurrentWorm().beginTurn();
}

void WormsList::add(physical_object_ptr worm){
	this->list.push_back(worm);
}

WormsList::WormsList(WormsList&& other):
	list(std::move(other.list)), current(other.current){}

void WormsList::distribute(size_t max, int life_to_add){
	if (this->list.size() < max){
		for (auto it = this->list.begin(); it != this->list.end(); ++it){
			Worm* worm = (Worm*)it->get();
			worm->addLife(life_to_add);
		}
	}
}

bool WormsList::isEmpty(){
	for (auto it = this->list.begin(); it != this->list.end(); ++it){
		if (!(*it)->isDead()){
			return false;
		}
	}
	return true;
}

void WormsList::kill(){
	for (auto it = this->list.begin(); it != this->list.end(); ++it){
		if (!(*it)->isDead()){
			(*it)->kill();
		}
	}
}

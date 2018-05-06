#include "Viewable.h"

Viewable::Viewable(WorldView& worldView): worldView(worldView){}

Viewable::~Viewable(){}

void Viewable::move(const Position& pos){
	this->worldView.moveElement(this->getWidget(), pos);
}

void Viewable::removeFromWorld(){
	this->worldView.removeElement(this->getWidget());
}

void Viewable::addToWorld(const Position& pos){
	this->worldView.addElement(this->getWidget(), pos);
}

Viewable::Viewable(Viewable&& other): worldView(other.worldView){}
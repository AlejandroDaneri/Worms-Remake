#include "Viewable.h"

#include <iostream>

Viewable::Viewable(WorldView& worldView): worldView(worldView){}

Viewable::~Viewable(){}

void Viewable::move(const Position& pos, float width, float height){
	this->worldView.moveElement(this->getWidget(), pos, width, height);
}

void Viewable::removeFromWorld(){
	this->worldView.removeElement(this->getWidget());
}

void Viewable::addToWorld(const Position& pos, float width, float height){
	this->worldView.addElement(this->getWidget(), pos, width, height);
}

Viewable::Viewable(Viewable&& other): worldView(other.worldView){}

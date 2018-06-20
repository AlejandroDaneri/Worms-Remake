#include "Viewable.h"
#include "WorldView.h"


Viewable::Viewable(WorldView& worldView) : has_focus(false),
										   worldView(worldView) {}

Viewable::~Viewable() {}

Viewable::Viewable(Viewable&& other) : has_focus(other.has_focus),
									   worldView(other.worldView) {}

void Viewable::move(const Position& pos) {
	this->worldView.moveElement(*this, pos);
}

void Viewable::removeFromWorld() {
	this->worldView.removeElement(this->getWidget());
}

void Viewable::addToWorld(const Position& pos) {
	this->worldView.addElement(*this, pos);
}

void Viewable::setFocus(bool focus) {
	this->has_focus = focus;
}

bool Viewable::hasFocus() const {
	return this->has_focus;
}

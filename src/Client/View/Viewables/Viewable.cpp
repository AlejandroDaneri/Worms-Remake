#include "Viewable.h"

Viewable::Viewable(WorldView& worldView) : worldView(worldView),
										   has_focus(false) {}

Viewable::~Viewable() {}

Viewable::Viewable(Viewable&& other) : worldView(other.worldView),
									   has_focus(other.has_focus) {}

void Viewable::move(const Position& pos, float width, float height) {
	this->worldView.moveElement(this->getWidget(), pos, width, height,
								this->has_focus);
}

void Viewable::removeFromWorld() {
	this->worldView.removeElement(this->getWidget());
}

void Viewable::addToWorld(const Position& pos, float width, float height) {
	this->worldView.addElement(this->getWidget(), pos, width, height,
							   this->has_focus);
}

void Viewable::setFocus(bool focus) {
	this->has_focus = focus;
}

bool Viewable::hasFocus() const {
	return this->has_focus;
}

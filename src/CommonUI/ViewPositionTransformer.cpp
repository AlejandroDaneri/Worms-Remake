#include "ViewPositionTransformer.h"
#include "ObjectSizes.h"

ViewPositionTransformer::ViewPositionTransformer(Gtk::Layout& layout): layout(layout){}

ViewPositionTransformer::~ViewPositionTransformer() {}

Position ViewPositionTransformer::transformToScreen(const Position& position) {
	guint width, height;
	this->layout.get_size(width, height);
	float x = SCALE_FACTOR * position.getX();
	float y = height - SCALE_FACTOR * position.getY();
	return Position(x, y);
}

Position ViewPositionTransformer::transformToScreenAndMove(const Position& position, float width, float height){
	Position pos = this->transformToScreen(position);
	Position moved(pos.getX() - SCALE_FACTOR * width / 2, pos.getY() - SCALE_FACTOR * height / 2);
	return moved;
}

Position ViewPositionTransformer::transformToPosition(const Position& position) {
	guint width, height;
	this->layout.get_size(width, height);
	float x = position.getX() / SCALE_FACTOR;
	float y = (height - position.getY()) / (SCALE_FACTOR);
	return Position(x, y);
}

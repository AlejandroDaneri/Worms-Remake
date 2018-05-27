#include "ViewTransformer.h"
#include "ObjectSizes.h"

ViewTransformer::ViewTransformer(Gtk::Layout& layout): layout(layout){}

ViewTransformer::~ViewTransformer() {}

Position ViewTransformer::transformToScreen(const Position& position) {
	guint width, height;
	this->layout.get_size(width, height);
	float x = SCALE_FACTOR * position.getX();
	float y = height - SCALE_FACTOR * position.getY();
	return Position(x, y);
}

Position ViewTransformer::transformToScreenAndMove(const Position& position, float width, float height){
	Position pos = this->transformToScreen(position);
	Position moved(pos.getX() - SCALE_FACTOR * width / 2, pos.getY() - SCALE_FACTOR * height / 2);
	return moved;
}

Position ViewTransformer::transformToPosition(const Position& position) {
	guint width, height;
	this->layout.get_size(width, height);
	float x = position.getX() / SCALE_FACTOR;
	float y = (height - position.getY()) / (SCALE_FACTOR);
	return Position(x, y);
}

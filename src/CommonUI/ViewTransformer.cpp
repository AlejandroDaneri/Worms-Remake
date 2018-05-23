#include "ViewTransformer.h"
#include "ObjectSizes.h"

ViewTransformer::ViewTransformer() {
	this->screen = Gdk::Screen::get_default();
}

ViewTransformer::~ViewTransformer() {}

Position ViewTransformer::transformToScreen(const Position& position) {
	float x = SCALE_FACTOR * position.getX();
	float y = this->screen->get_height() - SCALE_FACTOR * position.getY();
	return Position(x, y);
}

Position ViewTransformer::transformToScreenAndMove(const Position& position, float width, float height){
	Position pos = this->transformToScreen(position);
	Position moved(pos.getX() - SCALE_FACTOR * width / 2, pos.getY() - SCALE_FACTOR * height / 2);
	return moved;
}

Position ViewTransformer::transformToPosition(const Position& position) {
	float x = position.getX() / SCALE_FACTOR;
	float y = (this->screen->get_height() - position.getY()) / (SCALE_FACTOR);
	return Position(x, y);
}

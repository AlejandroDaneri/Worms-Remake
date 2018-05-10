#include "ViewTransformer.h"

#define SCALE_FACTOR 15

ViewTransformer::ViewTransformer() {
	this->screen = Gdk::Screen::get_default();
}

ViewTransformer::~ViewTransformer() {}

Position ViewTransformer::transformToScreen(const Position& position) {
	int x = SCALE_FACTOR * position.getX();
	int y = this->screen->get_height() - SCALE_FACTOR * position.getY();
	return Position(x, y);
}

Position ViewTransformer::transformToPosition(const Position& position) {
	int x = position.getX() / SCALE_FACTOR;
	int y = (this->screen->get_height() - position.getY()) / (SCALE_FACTOR);
	return Position(x, y);
}

#include "GirderView.h"
#include <string>
#include "GirderSize.h"

GirderView::GirderView(WorldView& worldView, size_t size, Position pos,
					   int rotation) :
		Viewable(worldView), size(size), rotation(rotation) {
	std::string path(GIRDER_PATH);
	path += std::to_string(size);
	path += "_";
	path += std::to_string(rotation);
	path += ".png";
	this->image.set(path);
	this->addToWorld(pos);
}

GirderView::~GirderView() {}

GirderView::GirderView(GirderView&& other) : Viewable(std::move(other)),
		image(std::move(other.image)), size(other.size),
		rotation(other.rotation) {}

Gtk::Widget& GirderView::getWidget() {
	return this->image;
}

float GirderView::getWidth() const {
	return GirderSize::getGirderWidthMeters(this->size, this->rotation);
}

float GirderView::getHeight() const {
	return GirderSize::getGirderHeightMeters(this->size, this->rotation);
}

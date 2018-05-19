#include "GirderView.h"
#include "ObjectSizes.h"

#define GIRDER_PATH "resources/images/Girder/girder_"

GirderView::GirderView(WorldView& worldView, size_t size, Position pos, int rotation):
	Viewable(worldView), size(size), rotation(rotation){

	std::string path(GIRDER_PATH);
	path += std::to_string(size);
	path += "_";
	path += std::to_string(rotation);
	path += ".png";
	this->image.set(path);
	this->addToWorld(pos, size, girder_height);
}

GirderView::~GirderView(){}

GirderView::GirderView(GirderView&& other): Viewable(std::move(other)),
	image(std::move(other.image)), size(other.size), rotation(other.rotation){}

Gtk::Widget& GirderView::getWidget(){
	return this->image;
}

#include "GirderView.h"
#include "ObjectSizes.h"
#include "Math.h"

GirderView::GirderView(WorldView& worldView, size_t size, Position pos, int rotation):
	Viewable(worldView), size(size), rotation(rotation){

	std::string path(GIRDER_PATH);
	path += std::to_string(size);
	path += "_";
	path += std::to_string(rotation);
	path += ".png";
	this->image.set(path);
	this->addToWorld(pos, this->getWidth(), this->getHeight());
}

GirderView::~GirderView(){}

GirderView::GirderView(GirderView&& other): Viewable(std::move(other)),
	image(std::move(other.image)), size(other.size), rotation(other.rotation){}

Gtk::Widget& GirderView::getWidget(){
	return this->image;
}

float GirderView::getHeight(){
	int angle = this->rotation;
	if (angle > 90){
		angle = 180 - angle;
	}
	return Math::sinDegrees(angle) * this->size + Math::cosDegrees(angle) * girder_height;
}

float GirderView::getWidth(){
	int angle = this->rotation;
	if (angle > 90){
		angle = 180 - angle;
	}
	return Math::cosDegrees(angle) * this->size + Math::sinDegrees(angle) * girder_height;
}

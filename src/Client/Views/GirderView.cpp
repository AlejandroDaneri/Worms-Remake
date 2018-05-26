#include "GirderView.h"
#include "ObjectSizes.h"
#include "math_utils.h"

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
	return Math::sin_degrees(angle) * this->size + Math::cos_degrees(angle) * girder_height;
}

float GirderView::getWidth(){
	int angle = this->rotation;
	if (angle > 90){
		angle = 180 - angle;
	}
	return Math::cos_degrees(angle) * this->size + Math::sin_degrees(angle) * girder_height;
}

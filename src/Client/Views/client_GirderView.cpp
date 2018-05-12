#include "GirderView.h"

GirderView::GirderView(WorldView& worldView, std::string girder, Position pos):
	Viewable(worldView), girder_name(std::move(girder)){

	std::string path(IMAGES_PATH);///////////////por ahora es mas eficiente porque es solo una imagen
	path += this->girder_name;
	path += ".png";
	this->image.set(path);
	this->addToWorld(pos);
}

GirderView::~GirderView(){}

GirderView::GirderView(GirderView&& other): Viewable(std::move(other)),
	image(std::move(other.image)), girder_name(std::move(other.girder_name)){}

void GirderView::updateData(const Position& new_pos){
	this->move(new_pos);
}

void GirderView::explode(){
	this->removeFromWorld();
}

Gtk::Widget& GirderView::getWidget(){
	////////////////////////////////////////////Ver que hacer con la rotacion, por ahora lo dejo asi
	/*std::string path(IMAGES_PATH);
	path += this->weapon_name;
	path += ".png";
	this->image.set(path);*/
	return this->image;
}


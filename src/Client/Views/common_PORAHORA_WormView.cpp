#include "WormView.h"
#include <string>

#define WORM_IMAGE "_worm.png"

WormView::WormView(WorldView& worldView, int life, Position pos):
	Viewable(worldView), life(life), dir(DIR_RIGHT){
		this->addToWorld(pos);
}

WormView::~WormView(){}

void WormView::updateData(int new_life, dir_t new_dir, const Position& new_pos){
	this->life = new_life;
	this->dir = new_dir;
	this->move(new_pos);
}

void WormView::kill(){
	this->removeFromWorld();
	////////////////////////////////////////Hacer sonido de gusano muerto
}


Gtk::Widget& WormView::getWidget(){
	////////////////////////////////Por ahora no uso la vida,         hacer un vbox con la bida y la imagen

	std::string path(IMAGES_PATH);
	if (this->dir == DIR_RIGHT){
		path += "right";
	} else {
		path += "left";
	}
	path += WORM_IMAGE;

	this->image.set(path);

	return this->image;
}

WormView::WormView(WormView&& other): Viewable(std::move(other)),
	life(other.life), dir(other.dir), image(std::move(other.image)){}
#include "WormView.h"
#include "ObjectSizes.h"
#include <string>

#define WORM_IMAGE "_worm.png"

WormView::WormView(WorldView& worldView, int life, char dir, Position pos, int player_id, const std::string& weapon):
	Viewable(worldView), player_id(player_id), life(life), dir(dir), dir_changed(true), weapon(weapon){
	    /*this->full_image = Gdk::Pixbuf::create_from_file("resources/images/walk.png");
	    int ancho = full_image->get_width();
	    int alto = full_image->get_height();
	    for (int i = 0; i < alto/60 -1; i++) {
			queue.push(Gdk::Pixbuf::create_subpixbuf(full_image, 0, i*60, ancho, ancho));
		}*/
		this->addToWorld(pos, worm_size, worm_size);
}

WormView::~WormView(){}

/*WormView::WormView(WormView&& other): Viewable(std::move(other)),
	life(other.life), dir(other.dir), queue(std::move(other.queue)),
	full_image(std::move(other.full_image)), image(std::move(other.image)){}*/
	
WormView::WormView(WormView&& other): Viewable(std::move(other)),
	life(other.life), dir(other.dir), image(std::move(other.image)){}

void WormView::updateData(int new_life, char new_dir, const Position& new_pos, const std::string& weapon){
	this->life = new_life;
	this->dir_changed = this->dir != new_dir;
	this->dir = new_dir;
	this->weapon = weapon;
	this->move(new_pos, worm_size, worm_size);
}

void WormView::kill(){
	this->removeFromWorld();
	////////////////////////////////////////Hacer sonido de gusano muerto
}


Gtk::Widget& WormView::getWidget(){
	////////////////////////////////Por ahora no uso la vida,         hacer un vbox con la vida y la imagen

	//////////////////////////hacer algo con el arma actual
	if (this->dir_changed){
		std::string path(IMAGES_PATH);
		if (this->dir == DIR_RIGHT){
			path += "right";
		} else {
			path += "left";
		}
		path += WORM_IMAGE;

		this->image.set(path);
		//this->queue.push(std::move(this->queue.front()));
		//this->queue.pop();
	}
	/*if (this->dir == DIR_RIGHT) {
		this->image.set(Gdk::Pixbuf::create_subpixbuf(this->queue.back(), 0, 0, 60, 60));
	} else {
		this->image.set(Gdk::Pixbuf::create_subpixbuf(this->queue.back(), 60, 0, 60, 60));
	}*/
	//this->worm.add(this->image);
	//this->worm.show();
	//return this->worm;
	return this->image;
}

const char WormView::getDir() const {
	return this->dir;
}


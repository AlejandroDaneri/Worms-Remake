#include "WormView.h"
#include "ObjectSizes.h"
#include "WeaponNames.h"
#include <string>
#include "GamePlayers.h"

#define WORM_IMAGE "worms/"
const int IMAGE_WIDTH = 30;

WormView::WormView(WorldView& worldView, int life, char dir, Position pos, int player_id):
	Viewable(worldView), player_id(player_id), life(life), dir(dir),
	weapon(BAZOOKA_NAME), last_position(Position(-1, -1)), label(life, colors[player_id]){
	    this->full_image = Gdk::Pixbuf::create_from_file("resources/images/walk2.png");
	    int width = full_image->get_width();
	    int height = full_image->get_height();
	    for (int i = 0; i < height/IMAGE_WIDTH -1; i++) {
			queue.push(Gdk::Pixbuf::create_subpixbuf(full_image, 0, i * IMAGE_WIDTH, width, IMAGE_WIDTH));
		}
		this->worm.attach(this->label.getWidget(), 0, 0, 1, 1);
		this->worm.attach(this->image, 0, 1, 1, 1);
		this->setStaticImage(true);
		this->addToWorld(pos, worm_size, worm_size + 0.5);
}

WormView::~WormView(){}
	
WormView::WormView(WormView&& other): Viewable(std::move(other)), player_id(other.player_id),
	life(other.life), dir(other.dir), weapon(std::move(other.weapon)), last_position(other.last_position), 
	label(std::move(other.label)),
	image(std::move(other.image)), worm(std::move(other.worm)),
	queue(std::move(other.queue)), full_image(std::move(other.full_image)) {}

void WormView::updateData(int new_life, char new_dir, const Position& new_pos, bool colliding, bool is_current_worm){
	if (new_life != this->life){
		this->label.updateLife(new_life);
	}
	this->life = new_life;
	bool dir_changed = this->dir != new_dir;
	bool moved = !(this->last_position == new_pos);
	this->dir = new_dir;
	this->last_position = new_pos;
	this->setNewImage(dir_changed, moved, colliding, is_current_worm);
	this->move(new_pos, worm_size, worm_size + 0.5);
}

void WormView::kill(){
	this->removeFromWorld();
	////////////////////////////////////////Hacer sonido de gusano muerto
}

void WormView::changeWeapon(const std::string& weapon) {
    this->weapon = weapon;
    this->setWeaponImage();
}

void WormView::setNewImage(bool dir_changed, bool moved, bool colliding, bool is_current_worm){
	if (is_current_worm){
		if (!moved){
			this->setWeaponImage();
		} else if (colliding){
			this->setMovementImage();
		}
		return;
	}
	this->setStaticImage(dir_changed);
}

void WormView::setWeaponImage(){
	std::string path(IMAGES_PATH);
    path += WORM_IMAGE;
    path += this->weapon;
    if (this->dir == DIR_RIGHT){
        path += "_right.png";
    } else {
        path += "_left.png";
    }
    this->image.set(path);
}

void WormView::setMovementImage(){
	this->queue.push(std::move(this->queue.front()));
	this->queue.pop();
	this->image.set(Gdk::Pixbuf::create_subpixbuf(this->queue.back(), IMAGE_WIDTH + this->dir * IMAGE_WIDTH, 0, IMAGE_WIDTH, IMAGE_WIDTH));
}

void WormView::setStaticImage(bool dir_changed){
	if (dir_changed){
		this->image.set(Gdk::Pixbuf::create_subpixbuf(this->queue.back(), IMAGE_WIDTH + this->dir * IMAGE_WIDTH, 0, IMAGE_WIDTH, IMAGE_WIDTH));
	}
}

Gtk::Widget& WormView::getWidget(){
	return this->worm;
}

int WormView::getLife() const{
	return this->life;
}

char WormView::getDir() const {
	return this->dir;
}

int WormView::getPlayerId() const{
	return this->player_id;
}

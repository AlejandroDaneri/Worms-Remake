#include "WalkingAnimation.h"
#include "Path.h"
#include "ObjectSizes.h"

#define DIR_RIGHT 1
#define DIR_LEFT -1

WalkingAnimation::WalkingAnimation(Gtk::Image* worm_image) : worm_image(worm_image),
	dir(DIR_RIGHT) {
	this->walk_image = Gdk::Pixbuf::create_from_file(WORMS_PATH + "walk.png");
	int width = this->walk_image->get_width();
	int height = this->walk_image->get_height();
	for (int i = 0; i < height / WORM_IMAGE_WIDTH; i++) {
		walk_queue.push(Gdk::Pixbuf::create_subpixbuf(this->walk_image, 0, i * WORM_IMAGE_WIDTH, width, WORM_IMAGE_WIDTH));
	}
}

WalkingAnimation::~WalkingAnimation() {}

WalkingAnimation::WalkingAnimation(WalkingAnimation&& other) :
	walk_queue(std::move(other.walk_queue)), walk_image(std::move(other.walk_image)),
	worm_image(other.worm_image), dir(other.dir) {}

void WalkingAnimation::setMovementImage(char new_dir) {
	if (new_dir == this->dir){
		this->walk_queue.push(std::move(this->walk_queue.front()));
		this->walk_queue.pop();
	}
	this->dir = new_dir;
	this->setStaticImage();
}

void WalkingAnimation::setStaticImage() {
	this->worm_image->set(Gdk::Pixbuf::create_subpixbuf(this->walk_queue.back(), WORM_IMAGE_WIDTH + this->dir * WORM_IMAGE_WIDTH, 0, WORM_IMAGE_WIDTH, WORM_IMAGE_WIDTH));
}

void WalkingAnimation::updateWormImage(Gtk::Image* worm_image) {
	this->worm_image = worm_image;
}

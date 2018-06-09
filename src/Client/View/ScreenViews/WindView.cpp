#include "WindView.h"
#include "Path.h"

WindView::WindView(): container(false, 7){
	this->container.pack_start(this->velocity, Gtk::PACK_SHRINK);
	this->container.pack_start(this->direction, Gtk::PACK_SHRINK);
	this->velocity.set_use_markup(true);
}

WindView::~WindView(){}

void WindView::update(float wind){
	wind *= 10;
	std::string message = "<span><b><u>Viento</u></b>\n\n";
	std::string direction = "right";
	if (wind == 0){
		direction = "no";
	} else if (wind < 0){
		wind *= -1;
		direction = "left";
	}
	std::string velocity = std::to_string(wind);
	message += velocity.substr(0,4) + "</span>";
	this->velocity.set_markup(message);
	this->direction.set(IMAGES_PATH + "arrow_" + direction + ".png");
}

Gtk::VBox& WindView::getWindow(){
	return this->container;
}

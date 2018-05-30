#include "WindView.h"
#include "Path.h"
#include <glibmm/main.h>

WindView::WindView(): container(false, 7){
	this->container.pack_start(this->velocity, Gtk::PACK_SHRINK);
	this->container.pack_start(this->direction, Gtk::PACK_SHRINK);
	this->velocity.set_use_markup(true);
}

WindView::~WindView(){}

void WindView::update(float wind){
	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &WindView::updateCallback), wind);
    Glib::signal_idle().connect(my_slot);
}

bool WindView::updateCallback(float wind){
	wind *= 10;
	std::string message = "<span><b><u>Viento</u></b>\n\n";
	std::string direction = "right";
	if (wind < 0){
		wind *= -1;
		direction = "left";
	}
	std::string velocity = std::to_string(wind);
	message += velocity.substr(0,4) + "</span>";
	this->velocity.set_markup(message);
	this->direction.set(IMAGES_PATH + "arrow_" + direction + ".png");
	return false;
}

Gtk::VBox& WindView::getWindow(){
	return this->container;
}

#include "ExplosionView.h"
#include <gtkmm/image.h>
#include <glibmm/main.h>
#include "Path.h"

ExplosionView::ExplosionView(BulletView&& bullet) : bulletView(
		std::move(bullet)) {
	this->animation = Gdk::Pixbuf::create_from_file(EXPLOSION_ANIMATION);
	int width = this->animation->get_width();
	int height = this->animation->get_height();
	for (int i = 0; i < height / width; i++) {
		Glib::RefPtr<Gdk::Pixbuf> aux = Gdk::Pixbuf::create_subpixbuf(
				this->animation, 0, i * width, width, width);
		this->animation_vector.push_back(aux);
	}
	this->iter = this->animation_vector.begin();
}

ExplosionView::~ExplosionView() {}

ExplosionView::ExplosionView(ExplosionView&& other) :
		bulletView(std::move(other.bulletView)) {
	this->animation_vector = other.animation_vector;
	this->animation = other.animation;
	this->iter = this->animation_vector.begin();
}

bool ExplosionView::startCallBack() {
	Gtk::Image& image = (Gtk::Image&) this->bulletView.getWidget();
	image.set(*(this->iter));
	this->iter++;
	if (this->iter == this->animation_vector.end()) {
		this->bulletView.removeFromWorld();
		return false;
	}
	return true;
}

void ExplosionView::start() {
	Glib::signal_timeout().connect(
			sigc::mem_fun(*this, &ExplosionView::startCallBack), 40);
}

bool ExplosionView::hasFinished() {
	return this->iter == this->animation_vector.end();
}

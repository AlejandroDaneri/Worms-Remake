#include "ExplosionView.h"
#include <gtkmm/image.h>
#include <glibmm/main.h>
#include "BulletView.h"
#include "ViewsList.h"

ExplosionView::ExplosionView(BulletView& bullet, ViewsList& viewList, int id) : bulletView(bullet),
	viewList(viewList), id(id) {
	this->animation = Gdk::Pixbuf::create_from_file("resources/images/animations/explosion.png");
    int width = this->animation->get_width();
    int height = this->animation->get_height();
    for (int i = 0; i < height/width; i++) {
	    Glib::RefPtr<Gdk::Pixbuf> aux = Gdk::Pixbuf::create_subpixbuf(this->animation, 0, i * width, width, width);
		this->animation_vector.push_back(aux);
	}
    this->iter = this->animation_vector.begin();
}

ExplosionView::~ExplosionView() {}

ExplosionView::ExplosionView(ExplosionView&& other) :
        bulletView(other.bulletView), viewList(other.viewList), id(other.id) {
    this->animation_vector = other.animation_vector;
    this->animation = other.animation;
    this->iter = this->animation_vector.begin();
}

bool ExplosionView::startCallBack() {
	Gtk::Image& image = (Gtk::Image&)this->bulletView.getWidget();
	image.set(*(this->iter));
	this->iter++;
	if (this->iter == this->animation_vector.end()) {
        this->viewList.eraseWeapon(this->id);
        return false;
    }
    return true;
}

void ExplosionView::start() {
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &ExplosionView::startCallBack), 40);
}

bool ExplosionView::hasFinished() {
    return this->iter == this->animation_vector.end();
}
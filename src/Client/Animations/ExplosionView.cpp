#include "ExplosionView.h"
#include <gtkmm/image.h>
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
}

ExplosionView::~ExplosionView() {}

void ExplosionView::run() {
	Gtk::Image& image = (Gtk::Image&)this->bulletView.getWidget();
	std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator iter;
	for (iter = this->animation_vector.begin(); iter != this->animation_vector.end(); iter++) {
		image.set(Gdk::Pixbuf::create_subpixbuf(*iter, 0, 0, 60, 60));
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
	}
	this->running = false;
	this->viewList.eraseWeapon(this->id);
}

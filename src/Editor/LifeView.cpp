
#include "LifeView.h"

LifeView::LifeView(BaseObjectType *cobject,
                   const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::SpinButton(cobject),
          default_hp(this->get_value()) {
}

void LifeView::reset() {
    this->set_value(default_hp);
}

void LifeView::update(const unsigned int &new_life) {
    this->set_value(new_life);
}

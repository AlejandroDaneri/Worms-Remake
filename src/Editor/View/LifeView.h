
#ifndef WORMS_LIFEVIEW_H
#define WORMS_LIFEVIEW_H


#include <gtkmm/spinbutton.h>
#include <gtkmm/builder.h>

class LifeView : public Gtk::SpinButton {
private:
    const unsigned int default_hp;
public:
    LifeView(BaseObjectType *cobject,
             const Glib::RefPtr<Gtk::Builder> &builder);

    void reset();

    void update(const unsigned int &new_life);
};


#endif //WORMS_LIFEVIEW_H

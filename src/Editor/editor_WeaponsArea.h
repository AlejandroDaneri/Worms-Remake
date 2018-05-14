
#ifndef WORMS_WEAPONSAREA_H
#define WORMS_WEAPONSAREA_H


#include <gtkmm/grid.h>
#include <gtkmm/button.h>

class WeaponsArea : public Gtk::Grid{
    Gtk::Button back;
public:
    WeaponsArea();

protected:
    bool on_button_release_event(GdkEventButton *release_event) override;
};


#endif //WORMS_WEAPONSAREA_H

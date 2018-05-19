
#ifndef WORMS_WEAPON_H
#define WORMS_WEAPON_H


#include <gtkmm/hvbox.h>
#include <gtkmm/image.h>
#include <gtkmm/levelbar.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/hvscale.h>
#include <gtkmm/checkbutton.h>

class Weapon : public Gtk::HBox{
    Gtk::Image img;
    //Glib::RefPtr<Gtk::Adjustment> m_adjustment;
    Gtk::HScale ammo;
    Gtk::CheckButton infinite;
public:
    Weapon();

    void on_ammo_value_change();

    void on_checkbox_clicked();

    void reset_ammo();
};


#endif //WORMS_WEAPON_H

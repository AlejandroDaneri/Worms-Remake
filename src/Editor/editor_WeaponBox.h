
#ifndef WORMS_WEP_H
#define WORMS_WEP_H


#include <gtkmm/hvbox.h>
#include <gtkmm/scale.h>
#include <gtkmm/checkbutton.h>
#include "editor_WeaponController.h"

class WeaponController;

class WeaponBox {
    Gtk::Scale* ammo_selector;
    Gtk::CheckButton* infinite;
    const bool default_checkbox_state;
    const int default_ammo_selector_value;
    WeaponController* controller;
public:
    WeaponBox(Gtk::Scale* pWidget, Gtk::CheckButton* pButton);

    void on_ammo_value_change();

    void on_checkbox_clicked();

    void reset_ammo();

    void linkController(WeaponController* controller);
};


#endif //WORMS_WEP_H

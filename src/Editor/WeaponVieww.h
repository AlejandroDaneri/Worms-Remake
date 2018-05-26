
#ifndef WORMS_WEP_H
#define WORMS_WEP_H


#include <gtkmm/hvbox.h>
#include <gtkmm/scale.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/builder.h>
#include "WeaponController.h"

class WeaponController;

class WeaponView {
    Gtk::Scale *ammo_selector;
    Gtk::CheckButton *infinite;
    bool default_checkbox_state;
    int default_ammo_selector_value;
    WeaponController *controller;
public:
    WeaponView(const Glib::RefPtr<Gtk::Builder> &builder,
               const unsigned int &id);

    void on_ammo_value_change();

    void on_checkbox_clicked();

    void resetAmmo();

    void linkController(WeaponController *controller);

    const int getInitialAmmo();

    void setAmmo(const int &ammo);
};


#endif //WORMS_WEP_H

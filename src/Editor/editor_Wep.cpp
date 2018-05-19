
#include <iostream>
#include "editor_Wep.h"

Wep::Wep(Gtk::Scale *pWidget, Gtk::CheckButton *pButton)
        : ammo_selector(pWidget),
          infinite(pButton)
{
    if(infinite->get_active()) {
        default_ammo = ammo = -1;
        ammo_selector->set_sensitive(false);
    }
    else
        default_ammo=ammo=ammo_selector->get_value();

    ammo_selector->signal_value_changed().connect(
            sigc::mem_fun(*this, &Wep::on_ammo_value_change));

    infinite->signal_clicked().connect(
            sigc::mem_fun(*this, &Wep::on_checkbox_clicked) );
}

void Wep::on_ammo_value_change(){ ////mejorar?
    ammo_selector->get_value();
}

void Wep::on_checkbox_clicked() {
    bool status = !infinite->get_active();
    ammo_selector->set_sensitive(status);
}

void Wep::reset_ammo() {
    ammo=default_ammo;
    if (default_ammo==-1){
        infinite->set_active(true);

    }
    else{
        infinite->set_active(false);
        ammo_selector->set_value(default_ammo);
    }


}

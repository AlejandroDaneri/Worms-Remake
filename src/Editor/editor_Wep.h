
#ifndef WORMS_WEP_H
#define WORMS_WEP_H


#include <gtkmm/hvbox.h>
#include <gtkmm/scale.h>
#include <gtkmm/checkbutton.h>

class Wep {//este nombre es temporal, para evitar merge conflict
    Gtk::Scale* ammo_selector;
    Gtk::CheckButton* infinite;
    int ammo,default_ammo;

public:
    Wep(Gtk::Scale *pWidget, Gtk::CheckButton *pButton);

    void on_ammo_value_change();

    void on_checkbox_clicked();

    void reset_ammo();
};


#endif //WORMS_WEP_H


#ifndef WORMS_WEAPONLISTT_H
#define WORMS_WEAPONLISTT_H

#include <gtkmm/builder.h>
//#include "_editor_WeaponsBar.h"
#include "editor_WeaponController.h"
#include "editor_WeaponModel.h"

class WeaponListt {
    Glib::RefPtr <Gtk::Builder> m_builder;
    std::vector<WeaponModel*> weapons;
    std::vector<WeaponBox> weapons_view;
    std::vector<WeaponController> wep_controllers;
public:
    WeaponListt(const Glib::RefPtr <Gtk::Builder> &builder);

    void reset_ammo();
};


#endif //WORMS_WEAPONLISTT_H

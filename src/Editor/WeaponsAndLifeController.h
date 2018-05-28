
#ifndef WORMS_WEAPONSLISTCONTROLLER_H
#define WORMS_WEAPONSLISTCONTROLLER_H


#include <gtkmm/button.h>
#include <gtkmm/spinbutton.h>
#include "WeaponModel.h"
#include "WeaponVieww.h"
#include "LifeView.h"

class WeaponsAndLifeController {
private:
    LifeView *life_spin;

    Gtk::Button *reset_button;
    std::vector<std::shared_ptr<WeaponModel>> weapons;
    std::vector<std::shared_ptr<WeaponView>> weapons_view;
    std::vector<std::shared_ptr<WeaponController> > wep_controllers;
public:
    explicit WeaponsAndLifeController(
            const Glib::RefPtr<Gtk::Builder> &builder);

    void on_reset_clicked();

    void getWeapons(std::vector<int> &weps_ammo, unsigned int &life) const;

    void
    loadWeapons(std::vector<int> &weps_ammo, const unsigned int &life) const;
};


#endif //WORMS_WEAPONSLISTCONTROLLER_H

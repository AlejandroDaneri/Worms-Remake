
#ifndef WORMS_WEAPONSLISTCONTROLLER_H
#define WORMS_WEAPONSLISTCONTROLLER_H


#include <gtkmm/button.h>
#include <gtkmm/spinbutton.h>
#include "Model/Weapon.h"
#include "View/WeaponView.h"
#include "View/LifeView.h"

class WeaponsAndLifeController {
private:
    LifeView *life_spin;

    Gtk::Button *reset_button;
    std::vector<std::shared_ptr<Weapon>> weapons;
    std::vector<std::shared_ptr<WeaponView>> weapons_view;
    std::vector<std::shared_ptr<WeaponController> > wep_controllers;
public:
    explicit WeaponsAndLifeController(
            const Glib::RefPtr<Gtk::Builder> &builder);

    void on_reset_clicked();

    void getWeapons(std::vector<int> &weps_ammo, unsigned int &life) const;

    void
    loadWeapons(std::vector<int> &weps_ammo, const unsigned int &life) const;

    bool isValidWeaponSet(std::vector<int> &ammo_vector) const;
};


#endif //WORMS_WEAPONSLISTCONTROLLER_H

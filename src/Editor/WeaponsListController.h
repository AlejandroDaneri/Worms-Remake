
#ifndef WORMS_WEAPONSLISTCONTROLLER_H
#define WORMS_WEAPONSLISTCONTROLLER_H


#include <gtkmm/button.h>
#include "WeaponModel.h"
#include "WeaponVieww.h"

class WeaponsListController {
private:
    //WeaponListt weapons;
    Gtk::Button *reset_button;
    std::vector<std::shared_ptr<WeaponModel>> weapons;
    std::vector<std::shared_ptr<WeaponView>> weapons_view;
    std::vector<std::shared_ptr<WeaponController> > wep_controllers;
public:
    WeaponsListController(const Glib::RefPtr<Gtk::Builder> &builder,
                          Gtk::Button *reset_button);

    void on_reset_clicked();

    const std::vector<int> &getWeapons() const;

    void getWeapons(std::vector<int> &weps_ammo) const;
};


#endif //WORMS_WEAPONSLISTCONTROLLER_H


#ifndef WORMS_WEAPONSLISTCONTROLLER_H
#define WORMS_WEAPONSLISTCONTROLLER_H


#include "editor_WeaponListt.h"

class WeaponsListController {
private:
    WeaponListt weapons;
    Gtk::Button *reset_button;
public:
    WeaponsListController(WeaponListt weapons, Gtk::Button *reset_button);

    void on_reset_clicked();
};


#endif //WORMS_WEAPONSLISTCONTROLLER_H


#ifndef WORMS_WEAPONSLISTCONTROLLER_H
#define WORMS_WEAPONSLISTCONTROLLER_H


#include <gtkmm/button.h>
#include <gtkmm/spinbutton.h>
#include "Weapon.h"
#include "WeaponView.h"
#include "LifeView.h"

// Clase que se encaga de manejar la comunicacion de la vida y el arma con las
// demas partes del programa
class UsablesController {
private:
    LifeView *life_spinner;
    Gtk::Button *reset_button;
    std::vector<std::shared_ptr<Weapon>> weapons;
    std::vector<std::shared_ptr<WeaponView>> weapons_view;
    std::vector<std::shared_ptr<WeaponController> > wep_controllers;

    // Indica si el set actual de armas es valido (alguno con municion positiva)
    bool isValidWeaponSet(std::vector<int> &ammo_vector) const;
public:
    explicit UsablesController(
            const Glib::RefPtr<Gtk::Builder> &builder);

    // Indica a los controladores de armas y vida que deben reiniciarse
    void onResetSignal();

    // Obtiene a los valores actuales de las armas y la vida
    void getWeaponsAndLife(std::vector<int> &weps_ammo, unsigned int &life) const;

    // Establece los valores de las armas y la vida
    void
    loadWeapons(std::vector<int> &weps_ammo, const unsigned int &life) const;


};


#endif //WORMS_WEAPONSLISTCONTROLLER_H

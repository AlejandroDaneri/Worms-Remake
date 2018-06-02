
#include "UsablesController.h"
#include "InvalidMapError.h"

UsablesController::UsablesController(
        const Glib::RefPtr<Gtk::Builder> &builder) {
    builder->get_widget("btn_reset", reset_button);
    reset_button->signal_clicked().connect(
            sigc::mem_fun(*this,
                          &UsablesController::on_reset_clicked));

    builder->get_widget_derived("life", life_spin);

    for (size_t i = 1; i <= 10; ++i) {
        std::shared_ptr<WeaponView> weapon_view(new WeaponView(builder, i));

        std::shared_ptr<Weapon> weapon
                (new Weapon(weapon_view->getInitialAmmo()));

        weapons.push_back(weapon);

        std::shared_ptr<WeaponController> weapon_controller(
                new WeaponController(weapon_view,
                                     weapon));
        wep_controllers.push_back(std::move(weapon_controller));
        weapons_view.push_back(weapon_view);
    }
}

void UsablesController::on_reset_clicked() {
    life_spin->reset();
    for (const std::shared_ptr<WeaponController> &actual_controller:wep_controllers) {
        actual_controller->resetAmmo();
    }
}

void UsablesController::getWeapons(std::vector<int> &weps_ammo,
                                          unsigned int &life) const {
    life = life_spin->get_value();
    for (const std::shared_ptr<WeaponController> &actual_controller:wep_controllers) {
        weps_ammo.push_back(actual_controller->getAmmo());
    }
    if (!isValidWeaponSet(weps_ammo)){
        throw InvalidMapError("Ningún arma tiene munición");
    }
}

void UsablesController::loadWeapons(std::vector<int> &weps_ammo,
                                           const unsigned int &life) const {
    int i = 0;
    for (const std::shared_ptr<WeaponController> &actual_controller
            :wep_controllers) {
        actual_controller->updateAmmo(weps_ammo[i]);
        i++;
    }
    life_spin->update(life);
}

bool
UsablesController::isValidWeaponSet(std::vector<int> &ammo_vector) const {
    int valid_weps_counter= 0;
    for (int actual_ammo : ammo_vector) {
        if(actual_ammo !=0)
            valid_weps_counter++;
    }
    return valid_weps_counter>0;
}

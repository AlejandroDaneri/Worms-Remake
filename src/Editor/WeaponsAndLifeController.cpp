
#include "WeaponsAndLifeController.h"
#include "InvalidMapError.h"

WeaponsAndLifeController::WeaponsAndLifeController(
        const Glib::RefPtr<Gtk::Builder> &builder) {
    builder->get_widget("btn_reset", reset_button);
    Gtk::manage(reset_button);
    reset_button->signal_clicked().connect(
            sigc::mem_fun(*this,
                          &WeaponsAndLifeController::on_reset_clicked));

    builder->get_widget_derived("life", life_spin);
    Gtk::manage(life_spin);

    for (size_t i = 1; i <= 10; ++i) {
        std::shared_ptr<WeaponView> weapon_view(new WeaponView(builder, i));

        std::shared_ptr<WeaponModel> weapon
                (new WeaponModel(weapon_view->getInitialAmmo()));

        weapons.push_back(weapon);

        std::shared_ptr<WeaponController> weapon_controller(
                new WeaponController(weapon_view,
                                     weapon));
        wep_controllers.push_back(std::move(weapon_controller));
        weapons_view.push_back(weapon_view);
    }
}

void WeaponsAndLifeController::on_reset_clicked() {
    life_spin->reset();
    for (const std::shared_ptr<WeaponController> &actual_controller:wep_controllers) {
        actual_controller->resetAmmo();
    }
}

void WeaponsAndLifeController::getWeapons(std::vector<int> &weps_ammo,
                                          unsigned int &life) const {
    life = life_spin->get_value();
    for (const std::shared_ptr<WeaponController> &actual_controller:wep_controllers) {
        weps_ammo.push_back(actual_controller->getAmmo());
    }
    if (!isValidWeaponSet(weps_ammo)){
        throw InvalidMapError("Ningún arma tiene munición");
    }
}

void WeaponsAndLifeController::loadWeapons(std::vector<int> &weps_ammo,
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
WeaponsAndLifeController::isValidWeaponSet(std::vector<int> &ammo_vector) const {
    bool valid_set= true;
    for (size_t i = 0; i<ammo_vector.size() && valid_set;i++) {
        valid_set=(ammo_vector[i]!=0);
    }
    return valid_set;
}


#include "WeaponsListController.h"

WeaponsListController::WeaponsListController(
        const Glib::RefPtr<Gtk::Builder> &builder,
        Gtk::Button *reset_button)
        : reset_button(reset_button)
{
    builder->get_widget_derived("life", life_spin);

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

void WeaponsListController::on_reset_clicked() {
    life_spin->reset();
    for (const std::shared_ptr<WeaponController> &actual_controller:wep_controllers) {
        actual_controller->resetAmmo();
    }
}

void WeaponsListController::getWeapons(std::vector<int> &weps_ammo, unsigned int &life) const {
    life=life_spin->get_value();
    for (const std::shared_ptr<WeaponController> &actual_controller:wep_controllers) {
        weps_ammo.push_back(actual_controller->getAmmo());
    }
}

void WeaponsListController::loadWeapons(std::vector<int> &weps_ammo, const unsigned int &life) const {
    int i = 0;
    for (const std::shared_ptr<WeaponController> &actual_controller
            :wep_controllers){
        actual_controller->updateAmmo(weps_ammo[i]);
        i++;
    }
    life_spin->update(life);
}

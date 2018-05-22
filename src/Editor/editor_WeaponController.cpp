
#include "editor_WeaponController.h"

WeaponController::WeaponController(std::shared_ptr<WeaponBox> View,
                                   std::shared_ptr<WeaponModel>model)
        : weapon_view(View),
          weapon_model(model) {}

void WeaponController::reset_ammo() {
    weapon_view->reset_ammo();
    weapon_model->reset_ammo();
}

void WeaponController::updateAmmo(double ammo) {
    weapon_model->set_ammo(ammo);
}

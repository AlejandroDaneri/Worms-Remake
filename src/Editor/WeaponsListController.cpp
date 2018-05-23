
#include "WeaponsListController.h"

WeaponsListController::WeaponsListController(WeaponListt weapons,
                                             Gtk::Button *reset_button)
        : weapons(weapons),
          reset_button(reset_button) {

}

void WeaponsListController::on_reset_clicked() {
    weapons.reset_ammo();
}

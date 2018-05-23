
#include <glibmm/refptr.h>

#include "WeaponListt.h"

WeaponListt::WeaponListt(const Glib::RefPtr<Gtk::Builder> &builder)
        : m_builder(builder) {

    for (int i = 0; i < 10; ++i) {
        Gtk::Scale *scale = nullptr;
        m_builder->get_widget("sc_wep" + std::to_string(i + 1), scale);
        Gtk::CheckButton *checkbox = nullptr;
        m_builder->get_widget("cb_wep" + std::to_string(i + 1), checkbox);
        std::shared_ptr<WeaponBox> weapon_view (new WeaponBox(scale, checkbox));

        int ammo;
        if (checkbox->get_active())
            ammo = -1;
        else
            ammo = scale->get_value();

        std::shared_ptr<WeaponModel> weapon (new WeaponModel(ammo));
        weapons.push_back(weapon);

        WeaponController *weapon_controller = new WeaponController(weapon_view,
                                                                   weapon);
        weapon_view->linkController(weapon_controller);

        wep_controllers.emplace_back(weapon_controller);
        weapons_view.push_back(weapon_view);

    }
}

void WeaponListt::reset_ammo() {
    for (WeaponController *actual_controller:wep_controllers) {
        actual_controller->reset_ammo();
    }
}

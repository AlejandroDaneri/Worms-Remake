#include "editor_WeaponBox.h"

WeaponBox::WeaponBox(Gtk::Scale *pWidget, Gtk::CheckButton *pButton)
        : ammo_selector(pWidget),
          infinite(pButton),
          default_checkbox_state(infinite->get_active()),
          default_ammo_selector_value(ammo_selector->get_value()),
          controller(nullptr) {
    ammo_selector->set_sensitive(!default_checkbox_state);

    ammo_selector->signal_value_changed().connect(
            sigc::mem_fun(*this, &WeaponBox::on_ammo_value_change));

    infinite->signal_clicked().connect(
            sigc::mem_fun(*this, &WeaponBox::on_checkbox_clicked));
}

void WeaponBox::on_ammo_value_change() {
    controller->updateAmmo(ammo_selector->get_value());
}

void WeaponBox::on_checkbox_clicked() {
    ammo_selector->set_sensitive(!infinite->get_active());
    if (infinite->get_active()) {
        controller->updateAmmo(-1);
    } else
        controller->updateAmmo(ammo_selector->get_value());
}

void WeaponBox::reset_ammo() {
    infinite->set_active(default_checkbox_state);
    ammo_selector->set_sensitive(!default_checkbox_state);
    ammo_selector->set_value(default_ammo_selector_value);
}

void WeaponBox::linkController(WeaponController *controller) {
    this->controller = controller;
}

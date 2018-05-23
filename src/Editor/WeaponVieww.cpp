#include "WeaponVieww.h"

WeaponView::WeaponView(const Glib::RefPtr<Gtk::Builder> &builder,
                       const unsigned int &id)
        : m_builder(builder) {

    m_builder->get_widget("sc_wep" + std::to_string(id), ammo_selector);
    m_builder->get_widget("cb_wep" + std::to_string(id), infinite);

    default_checkbox_state = infinite->get_active();
    default_ammo_selector_value = ammo_selector->get_value();

    ammo_selector->set_sensitive(!default_checkbox_state);

    ammo_selector->signal_value_changed().connect(
            sigc::mem_fun(*this, &WeaponView::on_ammo_value_change));

    infinite->signal_clicked().connect(
            sigc::mem_fun(*this, &WeaponView::on_checkbox_clicked));
}

void WeaponView::on_ammo_value_change() {
    controller->updateAmmo(ammo_selector->get_value());
}

void WeaponView::on_checkbox_clicked() {
    ammo_selector->set_sensitive(!infinite->get_active());
    if (infinite->get_active()) {
        controller->updateAmmo(-1);
    } else
        controller->updateAmmo(ammo_selector->get_value());
}

void WeaponView::resetAmmo() {
    infinite->set_active(default_checkbox_state);
    ammo_selector->set_sensitive(!default_checkbox_state);
    ammo_selector->set_value(default_ammo_selector_value);
}

void WeaponView::linkController(WeaponController *controller) {
    this->controller = controller;
}

const int WeaponView::getInitialAmmo() {
    return default_checkbox_state ? -1 : default_ammo_selector_value;
}

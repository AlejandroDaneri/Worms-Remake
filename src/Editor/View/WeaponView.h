
#ifndef WORMS_WEP_H
#define WORMS_WEP_H


#include <gtkmm/hvbox.h>
#include <gtkmm/scale.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/builder.h>
#include "WeaponController.h"
class WeaponController;

// Clase que contiene la vista de cada arma
class WeaponView {
private:
    Gtk::Scale *ammo_selector;
    Gtk::CheckButton *infinite;
    bool default_checkbox_state;
    int default_ammo_selector_value;
    WeaponController *controller;

public:
    WeaponView(const Glib::RefPtr<Gtk::Builder> &builder,
               const unsigned int &id);

    // Al cambiar el valor del scale se llama a este método.
    void onAmmoValueChanged();

    // Al cambiar el estado del checkbox  se llama a este método.
    void onCheckboxClicked();

    // Muestra la munición predeterminada de esta arma
    void resetAmmo();

    // Enlaza la vista al controlador
    void bindController(WeaponController *controller);

    // Obtiene la munición inicial
    const int getInitialAmmo();

    // Establece la munición a mostrar
    void setAmmo(const int &ammo);
};


#endif //WORMS_WEP_H

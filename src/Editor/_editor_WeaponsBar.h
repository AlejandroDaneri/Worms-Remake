
#ifndef WORMS_WEAPONSBAR_H
#define WORMS_WEAPONSBAR_H


#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include "editor_WeaponBox.h"
#include "editor_WeaponModel.h"

class WeaponsBar : public Gtk::Box{
private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    std::vector<WeaponModel> weapons; //es Weapon
    Gtk::Button* reset_button;
public:
    WeaponsBar(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

    void on_reset_clicked();
};


#endif //WORMS_WEAPONSBAR_H

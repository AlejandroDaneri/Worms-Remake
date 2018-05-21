
#include <gtkmm/scale.h>
#include <gtkmm/checkbutton.h>
#include "_editor_WeaponsBar.h"
#include "editor_WeaponBox.h"

WeaponsBar::WeaponsBar(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Box(cobject),
          m_builder(builder)
{
    //// cambiar por dynamic_cast?
    unsigned long size = this->get_children().size();
    for (unsigned long i = 0; i < size; ++i) {
        Gtk::Scale* scale = nullptr;
        m_builder->get_widget("sc_wep"+std::to_string(i+1),scale);
        Gtk::CheckButton* checkbox = nullptr;
        m_builder->get_widget("cb_wep"+std::to_string(i+1),checkbox);
        Weapon *wep = new Weapon(scale, checkbox); // para evitar segfault, unique_ptr tampoco sirve
        weapons.push_back(*wep);
    }
    m_builder->get_widget("btn_reset_wep",reset_button);

    reset_button->signal_clicked().connect(
            sigc::mem_fun(*this, &WeaponsBar::on_reset_clicked));
}

void WeaponsBar::on_reset_clicked() {
    for (Weapon wep : weapons){
        wep.reset_ammo();
    }
}

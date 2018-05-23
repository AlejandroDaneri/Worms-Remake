
#include <iostream>
#include "editor_WeaponView.h"
#define MAX_AMMO 51
#define CHANGE_AMMO_STEP 1

Weapon::Weapon(): Gtk::HBox(Gtk::ORIENTATION_HORIZONTAL,15),
                  //m_adjustment(Gtk::Adjustment::create(10, 0, 100, 1, 50, 50) ),
                  ammo(0,MAX_AMMO,CHANGE_AMMO_STEP),
                  infinite("∞")
{
    img.set("resources/images/Weapons_icons/Bazooka.png");
    ammo.set_value(5);
    pack_start(img);

    pack_end(infinite);
    pack_end(ammo);
    ammo.set_size_request(100,-1);

    ammo.signal_value_changed().connect( //poner sonido si quiere cambiarse y no se puede
            sigc::mem_fun(*this, &Weapon::on_ammo_value_change));

    infinite.signal_clicked().connect(
            sigc::mem_fun(*this, &Weapon::on_checkbox_clicked) );
}

void Weapon::on_ammo_value_change(){
    std::cout<<ammo.get_value()<<std::endl;
}

void Weapon::on_checkbox_clicked() {
    ammo.set_sensitive(!infinite.get_active());
}

void Weapon::reset_ammo() {
    ammo.set_value(5);
    infinite.set_active(false);
}



#include "editor_WeaponsArea.h"

WeaponsArea::WeaponsArea(): back("VOLVER"),m_default("RESETEAR") {
    add(back);
    attach_next_to(wep,back, Gtk::POS_BOTTOM,10,1);
    attach_next_to(m_default,wep, Gtk::POS_BOTTOM,10,1);
    m_default.signal_clicked().connect(sigc::mem_fun(*this,
                                                    &WeaponsArea::on_reset_clicked) );
    show_all_children();
}

bool WeaponsArea::on_button_release_event(GdkEventButton *release_event) {
    return false;
}

void WeaponsArea::on_reset_clicked(){
    wep.reset_ammo();
}

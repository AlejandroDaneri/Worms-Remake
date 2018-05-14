
#include "editor_WeaponsArea.h"

WeaponsArea::WeaponsArea() {
    back.set_label("VOLVER");
    add(back);
    show_all_children();
}

bool WeaponsArea::on_button_release_event(GdkEventButton *release_event) {
    return false;
}


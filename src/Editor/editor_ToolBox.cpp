#include <iostream>
#include "editor_ToolBox.h"

ToolBox::ToolBox() {
    worm.add_pixlabel("resources/images/right_worm.png","");
    girder.add_pixlabel("resources/images/grdl.png","");
    add(girder);
    attach_next_to(worm,girder, Gtk::POS_BOTTOM,2,1);

    turn.set_label("GIRAR");
    attach_next_to(turn,worm, Gtk::POS_BOTTOM, 2, 1);

    worm.signal_clicked().connect( sigc::bind<int>
            (sigc::mem_fun(*this,&ToolBox::on_button_clicked),WORM_BUTTON_ID));
    girder.signal_clicked().connect( sigc::bind<int>
            (sigc::mem_fun(*this, &ToolBox::on_button_clicked),
             GIRDER_BUTTON_ID ));
}

void ToolBox::on_button_clicked(int id) {
    if(id ==WORM_BUTTON_ID) {
        if (worm.get_active()) {
            item_pressed = WORM_BUTTON_ID;
            girder.set_active(false);
        }
    } else {
        if (girder.get_active()) {
            item_pressed = GIRDER_BUTTON_ID;
            worm.set_active(false);
        }
    }
}

std::string ToolBox::getActualItemImagePath() {
    switch (item_pressed){
        case WORM_BUTTON_ID:
            return "resources/images/right_worm.png";
        case GIRDER_BUTTON_ID:
            return "resources/images/grdl.png";

    }

}


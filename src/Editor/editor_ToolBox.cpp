#include <iostream>
#include "editor_ToolBox.h"

ToolBox::ToolBox():change_win(false) {
    worm.add_pixlabel("resources/images/right_worm.png","");
    girder.add_pixlabel("resources/images/grdl.png","");
    add(girder);
    attach_next_to(worm,girder, Gtk::POS_BOTTOM,2,1);

    turn.set_label("GIRAR");
    attach_next_to(turn,worm, Gtk::POS_BOTTOM, 2, 1);

    armory.set_label("Armas");
    attach_next_to(armory,turn, Gtk::POS_BOTTOM, 2, 1);

    armory.signal_clicked().connect( sigc::bind<int>
                                           (sigc::mem_fun(*this,&ToolBox::on_button_clicked),3));


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
        change_win= false;
    } else if(id== GIRDER_BUTTON_ID){
        if (girder.get_active()) {
            item_pressed = GIRDER_BUTTON_ID;
            worm.set_active(false);
        }
        change_win= false;
    }else{
        change_win= true;
    }
}



std::string ToolBox::getActualItemImagePath() {
    switch (item_pressed){
        case WORM_BUTTON_ID:
            return "resources/images/right_worm.png";
        case GIRDER_BUTTON_ID:
            return "resources/images/grdl.png";
    }
    return "a";

}

bool ToolBox::on_button_release_event(GdkEventButton *release_event) {
    return !change_win;
}




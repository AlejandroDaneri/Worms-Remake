#include <iostream>
#include "editor_ToolBox.h"

ToolBox::ToolBox() {
    worm.add_pixlabel("resources/images/right_worm.png","");
    girder.add_pixlabel("resources/images/grdl.png","");
    add(girder);
    attach_next_to(worm,girder, Gtk::POS_BOTTOM,2,1);

    turn.add_pixlabel("resources/images/right_worm.png","");
    attach_next_to(turn,worm, Gtk::POS_BOTTOM, 2, 1);

    worm.signal_clicked().connect( sigc::mem_fun(*this,
                                                     &ToolBox::on_button_clicked) );
}

void ToolBox::on_button_clicked() {

}
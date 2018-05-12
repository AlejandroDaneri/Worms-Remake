#include <iostream>
#include "editor_ToolBox.h"

ToolBox::ToolBox() {
    worm.add_pixlabel("resources/images/right_worm.png","");
    worm.set_size_request(20,20); // no funciona
    girder.add_pixlabel("resources/images/grdl.png","");
    pack_start(worm,false,false,10);
    pack_start(girder,false,false,10);

    worm.signal_clicked().connect( sigc::mem_fun(*this,
                                                     &ToolBox::on_button_clicked) );
}

void ToolBox::on_button_clicked()
{
    std::cout << "The Button was clicked." << std::endl;
}
#include <iostream>
#include "editor_ToolBox.h"

editor_ToolBox::editor_ToolBox() {
    worm.add_pixlabel("resources/images/right_worm.png","");
    worm.set_size_request(20,20); // no funciona
    girder.add_pixlabel("resources/images/grdl.png","");
    pack_start(worm,false,false,10);
    pack_start(girder,false,false,10);

    worm.signal_clicked().connect( sigc::mem_fun(*this,
                                                     &editor_ToolBox::on_button_clicked) );
}

void editor_ToolBox::on_button_clicked()
{
    std::cout << "The Button was clicked." << std::endl;
}
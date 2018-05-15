
#include "editor_MapEditor.h"


MapEditor::MapEditor() :mapArea(&toolBox){
    grandpa.append_page(mapTab,"first");
    mapTab.pack_start(toolBox,Gtk::PACK_SHRINK);
    mapTab.pack_end(mapArea);

    grandpa.append_page(wepTab,"page2");
    wepTab.pack_start(wepArea);
    grandpa.set_show_tabs(false);
    add(grandpa);

    show_all_children();
    maximize();
}

bool MapEditor::on_button_release_event(GdkEventButton *release_event) {
    if(release_event->y_root<250){ //probando, cambiar
        grandpa.prev_page();
        return true;
    }
    grandpa.next_page();
    return true;
}

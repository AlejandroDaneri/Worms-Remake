
#include "editor_Editor.h"


Editor::Editor() :mapArea(&toolBox){
    generalContainer.append_page(mapTab,"");
    mapTab.pack_start(toolBox,Gtk::PACK_SHRINK);
    mapTab.pack_end(mapArea);

    generalContainer.append_page(wepTab,"");
    wepTab.pack_start(wepArea);
    generalContainer.set_show_tabs(false);
    add(generalContainer);

    show_all_children();
    maximize();
}

bool Editor::on_button_release_event(GdkEventButton *release_event) {
    if(release_event->y_root<37){ //probando, cambiar
        generalContainer.prev_page();
        return true;
    }
    generalContainer.next_page();
    return true;
}

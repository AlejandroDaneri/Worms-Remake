
#include "editor_MapEditor.h"


MapEditor::MapEditor() :mapArea(&toolBox){
    parent.pack_start(toolBox,Gtk::PACK_SHRINK);
    parent.pack_end(mapArea);

    add(parent);

    show_all_children();
    maximize();
}

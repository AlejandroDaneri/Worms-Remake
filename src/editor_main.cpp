#include <gtkmm/application.h>
#include <gtkmm/grid.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/window.h>

#include "Editor/editor_ToolBox.h"
#include "Editor/editor_MapArea.h"

int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv);

    Gtk::Window window;
    Gtk::HBox general;
    MapArea mapArea;
    Gtk::AspectFrame aspectFrame("", /* label */
                                 Gtk::ALIGN_CENTER, /* center x */
                                 Gtk::ALIGN_CENTER, /* center y */
                                 0.8, /* xsize/ysize */
                                 false /* ignore child's aspect */);
    ToolBox toolBox;

    window.maximize();

    toolBox.show();
    general.pack_start(toolBox,Gtk::PACK_SHRINK);

    general.pack_end(mapArea);

    window.add(general);

    window.show_all_children();

    return app->run(window);
}

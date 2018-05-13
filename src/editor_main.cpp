#include <gtkmm/application.h>
#include "Editor/editor_MapEditor.h"

int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv);
    MapEditor mapEditor;
    return app->run(mapEditor);
}

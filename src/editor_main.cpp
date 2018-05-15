#include <gtkmm/application.h>
#include "Editor/editor_Editor.h"

int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv);
    Editor mapEditor;
    return app->run(mapEditor);
}

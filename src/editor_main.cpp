#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <giomm.h>
#include <iostream>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/window.h>
#include "editor_Toolbox.h"
#include "editor_Map.h"

int main (int argc, char *argv[])
{
    Gtk::Window* pMainWindow = nullptr;
    auto app = Gtk::Application::create(argc, argv);
    auto refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("editor.glade");
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }
    refBuilder->get_widget("window", pMainWindow);
    if(pMainWindow)
    {
        pMainWindow->maximize();

        Gtk::ScrolledWindow* mapw= nullptr;
        refBuilder->get_widget("mapw",mapw);

        Map* map= nullptr;
        refBuilder->get_widget_derived("map",map);

        Toolbox* toolbox = nullptr;
        refBuilder->get_widget_derived("toolbox",toolbox);
        toolbox->link_map(map);

        mapw->override_background_color(Gdk::RGBA("lightgreen"));

        pMainWindow->show_all_children();
        app->run(*pMainWindow);
    }

    return 0;
}

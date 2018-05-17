#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <giomm.h>
#include <iostream>
#include "Editor/editor_Editor.h"

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
        //Editor editor(&refBuilder);
        app->run(*pMainWindow);
    }

    delete pMainWindow;
    return 0;
}

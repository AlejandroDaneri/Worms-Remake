#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <gtk/gtk.h>

#include <iostream>
#include <cairo.h>



void on_salir_clicked(Glib::RefPtr<Gtk::Application> app){
    std::cout << "[recibido el evento clicked]" << std::endl;
      //Salimos del loop de eventos
    app->quit();
}

int main(int argc, char** argv) {
    auto app = Gtk::Application::create(argc, argv);
    Gtk::Window ventana;
    Gtk::Grid mainGrid;
	Gtk::Button buttonQuit;
    ventana.set_default_size(200, 200);
	Gtk::Image image;
	Gtk::Image bomba;
	image.set("resources/images/gtk.png");
	bomba.set("resources/images/bomba.png");
	mainGrid.attach(image,0,0,1,1);
	mainGrid.attach(bomba,10000,10000,1,1);
	
	buttonQuit.add_label("Quit");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app));
	
	mainGrid.attach(buttonQuit,0,2,1,1);
	ventana.add(mainGrid);
    ventana.show_all();
    return app->run(ventana);
}

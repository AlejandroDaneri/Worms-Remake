#include <glib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>

#include <string>
#include <queue>

void on_salir_clicked(Glib::RefPtr<Gtk::Application> app, Gtk::Image* image,std::queue<std::string>& cola){
	std::string& path = cola.front();
	image->set(path);
	cola.push(path);
	cola.pop();
}

int main (int argc, char** argv) {
	auto app = Gtk::Application::create(argc, argv);
	
	std::queue<std::string> cola;
	
    Gtk::Window ventana;
    Gtk::Grid grid;
    Gtk::Image bomba1;
	Gtk::Button buttonQuit;
	bomba1.set("resources/images/1.png");
	grid.attach(bomba1, 0,0,1,1);
	for (int i = 1; i <= 15; i++) 
		cola.push("resources/images/" + std::to_string(i) + ".png");
	
	buttonQuit.add_label("Mover");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app, &bomba1, cola));
	
	grid.attach(buttonQuit,0,2,1,1);
	ventana.add(grid);
    ventana.show_all();
    app->run(ventana);
	return 0;
}

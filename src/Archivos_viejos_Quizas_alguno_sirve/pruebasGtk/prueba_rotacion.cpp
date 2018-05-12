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

#include <queue>

void on_salir_clicked(Glib::RefPtr<Gtk::Application> app, std::queue<Gtk::Image*>& cola){
	Gtk::Image* imagen = cola.front();
	imagen->hide();
	cola.push(imagen);
	cola.pop();
	cola.front()->show();
}

int main (int argc, char** argv) {
	auto app = Gtk::Application::create(argc, argv);
	
	std::queue<Gtk::Image*> cola;
	
    Gtk::Window ventana;
    Gtk::Grid grid;
    Gtk::Image bomba1;
    Gtk::Image bomba2;
    Gtk::Image bomba3;
    Gtk::Image bomba4;
	Gtk::Button buttonQuit;
	bomba1.set("resources/images/gtk.png");
	bomba2.set("resources/images/image10.png");
	bomba3.set("resources/images/image11.png");
	bomba4.set("resources/images/image12.png");
	grid.attach(bomba1, 0,0,1,1);
	grid.attach(bomba2, 0,0,1,1);
	grid.attach(bomba3, 0,0,1,1);
	grid.attach(bomba4, 0,0,1,1);
	cola.push(&bomba1);
	cola.push(&bomba2);
	cola.push(&bomba3);
	cola.push(&bomba4);
	
	buttonQuit.add_label("rotar");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app, cola));
	
	grid.attach(buttonQuit,0,2,1,1);
	ventana.add(grid);
    ventana.show_all();
    bomba2.hide();
    bomba3.hide();
    bomba4.hide();
    app->run(ventana);
	return 0;
}

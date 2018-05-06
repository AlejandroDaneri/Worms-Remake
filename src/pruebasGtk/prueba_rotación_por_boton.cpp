#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gdkmm/pixbufanimation.h>

#include <iostream>
#include <cairo.h>



void Action_clicked(Glib::RefPtr<Gdk::PixbufAnimation>& Animation, Gtk::Image* image, bool& is_static){
    if (is_static)
    	image->set(Animation);
	else
		image->set(Animation->get_static_image());
	is_static = !is_static;
}

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
	Gtk::Button Action;
    ventana.set_default_size(200, 200);
    bool is_static = true;
	Glib::RefPtr<Gdk::PixbufAnimation> rot =  Gdk::PixbufAnimation::create_from_file("gtk1.gif");
	Gtk::Image bomba(rot->get_static_image());

	mainGrid.attach(bomba,0,0,1,1);
	
	Action.add_label("Action");
	Action.signal_clicked().connect(sigc::bind(sigc::ptr_fun(Action_clicked), rot, &bomba, is_static));
	
	buttonQuit.add_label("Quit");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app));
	
	mainGrid.attach(buttonQuit,0,2,1,1);
	mainGrid.attach(Action,0,3,1,1);
	ventana.add(mainGrid);
    ventana.show_all();
    return app->run(ventana);
} 

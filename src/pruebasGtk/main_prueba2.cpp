#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>
#include <gdk/gdkkeysyms.h>

#include <iostream>
#include <cairo.h>

#include "Thread.h"

class Functor: public Thread{
	public:
		Gtk::Fixed& window;
		Gtk::Image& image;
		Gtk::Image i2;

		Functor(Gtk::Fixed& w, Gtk::Image& i):
			window(w), image(i){
				i2.set("resources/images/bomba.png");
				this->window.put(this->i2,100, 100);
				window.signal_key_press_event().connect(sigc::mem_fun(*this, &Functor::on_my_key_press_event));
			}

			~Functor(){
				std::cout << "destroy" << std::endl;
			}

			void stop(){}

			void run(){
					sleep(2);
					std::cout << "move en la pantalla" << std::endl;

					this->window.move(this->image,500, 500);

					sleep(2);
					std::cout << "move fuera de pantalla" << std::endl;

					this->window.move(this->image,1300, 500);

					sleep(4);
					std::cout << "move a la pantalla" << std::endl;

					this->window.move(this->image,500, 500);

					sleep(2);
					std::cout << "remove de la pantalla" << std::endl;
					//this->window.remove(this->image);
			}

			bool on_my_key_press_event(GdkEventKey* key_event){
				std::cout << "key event = " << key_event->string << std::endl;
				this->window.move(this->image,200, 200);
				return true;

			}
};

void on_salir_clicked(Glib::RefPtr<Gtk::Application> app){
    std::cout << "[recibido el evento clicked]" << std::endl;
      //Salimos del loop de eventos
    app->quit();
}


int main(int argc, char** argv) {
    auto app = Gtk::Application::create(argc, argv);
    Gtk::Window ventana;
    Gtk::Fixed world_map;
    Gtk::ScrolledWindow map;
    map.add(world_map);
    //map.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
	Gtk::Button buttonQuit;
    ventana.resize(1000, 1000);
	Gtk::Image image;
	Gtk::Image bomba;
	image.set("resources/images/bomba2.png");
	bomba.set("resources/images/bomba.png");
	world_map.put(image,500,800);
	world_map.put(bomba,500, 800);
	
	buttonQuit.add_label("Quit");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app));
	
	world_map.put(buttonQuit,300, 300);
	ventana.add(map);
    ventana.show_all();

    Functor f(world_map, bomba);
    f.start();
    app->run(ventana);

    f.join();
	return 0;
}

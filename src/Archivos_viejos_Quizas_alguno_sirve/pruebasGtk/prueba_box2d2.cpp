#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>

#include <iostream>
#include <cairo.h>
#include "Box2D.h"

#include "Thread.h"

const float kPixelsPerMeter = 32.0f;

class Imagen: public Thread{
public:
	Gtk::Image& image;
	Gtk::Fixed& map;
	b2Body* body;

	Imagen(Gtk::Image& i, Gtk::Fixed& f):image(i), map(f){
		this->map.signal_key_press_event().connect(sigc::mem_fun(*this, &Imagen::on_my_key_press_event));
	}

	~Imagen(){}

	void addToWorld(b2World* world){
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(100,400);
		bodyDef.userData = this;
		bodyDef.fixedRotation = true;
		this->body = world->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1,1);
		  
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		this->body->CreateFixture(&boxFixtureDef);
	}

	b2Vec2 getPosition(){
		return this->body->GetPosition();
	}

	void stop(){
		this->running = false;
	}

	void run(){
		while (this->running){
			b2Vec2 pos = this->getPosition();
			std::cout << "Pos x: " << pos.x << "  y: " << pos.y << std::endl;
			map.move(image, pos.x, 900 - pos.y);
		}
	}

	bool on_my_key_press_event(GdkEventKey* key_event){
		std::cout << "key event = " << key_event->string << std::endl;
		this->body->ApplyForceToCenter( b2Vec2(0,100), true);
		return true;

	}
};

class MyWorld: public Thread{
public:
	b2World* world;

	MyWorld(){
		world = new b2World(b2Vec2(0.0f, -10.0));
		world->SetAllowSleeping(true);
		world->SetContinuousPhysics(true);
		//world->SetContactListener(this);


		//Viga en el piso
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody; //this will be a static body
		myBodyDef.position.Set(0, 0); //slightly lower position
		b2Body* staticBody = this->world->CreateBody(&myBodyDef); //add body to world


		b2PolygonShape boxShape;
		boxShape.SetAsBox(100000,1);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		staticBody->CreateFixture(&boxFixtureDef); //add fixture to body
	}

	~MyWorld(){
		delete this->world;
	}

	void stop(){
		this->running = false;
	}

	void run(){
		while(this->running){
			float32 timeStep = 1/60.0;      //the length of time passed to simulate (seconds)
			  int32 velocityIterations = 8;   //how strongly to correct velocity
			  int32 positionIterations = 3;   //how strongly to correct position
			  
			  this->world->Step( timeStep, velocityIterations, positionIterations);
			  std::this_thread::sleep_for (std::chrono::milliseconds(20));

		}
	}

	void add_imagen(Imagen& imagen){
		imagen.addToWorld(this->world);
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
    //world_map.set_gravity(Gdk::GRAVITY_SOUTH_WEST);
    //map.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
	Gtk::Button buttonQuit;
    ventana.resize(1000, 1000);
	Gtk::Image bomba;
	bomba.set("resources/images/bomba.png");
	world_map.put(bomba,500, 500);
	
	buttonQuit.add_label("Quit");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app));
	
	world_map.put(buttonQuit,300, 300);
	ventana.add(map);
	//ventana.set_gravity(Gdk::GRAVITY_SOUTH_WEST);
    ventana.show_all();
    //ventana.set_gravity(Gdk::GRAVITY_SOUTH_WEST);

    Imagen imagen(bomba, world_map);
    MyWorld w;
    w.add_imagen(imagen);
    w.start();
    imagen.start();
    app->run(ventana);
    imagen.stop();
    imagen.join();
    w.stop();
    w.join();
    std::cout << ventana.property_gravity() << std::endl;
	return 0;
}

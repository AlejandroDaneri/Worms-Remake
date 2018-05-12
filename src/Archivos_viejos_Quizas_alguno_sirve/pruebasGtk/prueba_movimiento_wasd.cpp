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

#include <string>
#include <queue>

#include "Thread.h"
#include <mutex>


std::queue<std::string> cola;

class UserData{
public:
	std::string type;
	b2Body* body;

	UserData(){}
	void setDatos(std::string type, b2Body* body){
		this->type = type;
		this->body = body;
	}
	~UserData(){}

};

class CollisionListener: public b2ContactListener{
public:
	CollisionListener(){}
	~CollisionListener(){}

	void BeginContact(b2Contact* contact){
		UserData* dataA = (UserData*)contact->GetFixtureA()->GetBody()->GetUserData();
		UserData* dataB = (UserData*)contact->GetFixtureB()->GetBody()->GetUserData();

		if (dataA->type == "Imagen" && dataB->type == "Imagen"){
			std::cout << "Colision" << std::endl;
			b2Vec2 pos = dataA->body->GetPosition();
			std::cout << "Pos x: " << pos.x << "  y: " << pos.y << "  isAwake: " << dataA->body->IsAwake() << std::endl;
			dataA->body->ApplyLinearImpulse(b2Vec2(-500, -500), dataA->body->GetWorldCenter(), true);
			std::cout << "ColisionA" << std::endl;
			dataB->body->ApplyLinearImpulse(b2Vec2(500, -500), dataB->body->GetWorldCenter(), true);
			std::cout << "ColisionB" << std::endl;
		}
	}
};

class Imagen: public Thread{
public:
	Gtk::Image& image;
	Gtk::Fixed& map;
	b2Body* body;
	int pos;
	std::mutex& mutex;
	UserData data;

	Imagen(Gtk::Image& i, Gtk::Fixed& f, int pos, bool signal, std::mutex& mutex):image(i), map(f), pos(pos), mutex(mutex){
		if (signal){
			this->map.signal_key_press_event().connect(sigc::mem_fun(*this, &Imagen::on_my_key_press_event));
		}
	}

	~Imagen(){}

	void addToWorld(b2World* world){
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(this->pos,500);

		bodyDef.fixedRotation = true;
		this->body = world->CreateBody(&bodyDef);
		data.setDatos("Imagen", this->body);
		this->body->SetUserData(&data);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1,1);
		  
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 4;
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
			//////////////////////std::cout << "Pos x: " << pos.x << "  y: " << pos.y << "  isAwake: " << this->body->IsAwake() << std::endl;
			std::this_thread::sleep_for (std::chrono::milliseconds(15));
			//std::lock_guard<std::mutex> lock(this->mutex);
			map.move(image, pos.x, pos.y);
		}
	}

	bool on_my_key_press_event(GdkEventKey* key_event){
		std::cout << "key event = " << key_event->string << std::endl;
		if (key_event->keyval == 'a'){
			this->body->SetLinearVelocity(b2Vec2(-100, 0));
			std::string& path = cola.front();
			this->image.set(path);
			cola.push(path);
			cola.pop();
			std::this_thread::sleep_for (std::chrono::milliseconds(15));
			this->body->SetLinearVelocity(b2Vec2(0, 0));
			return true;
		}
		if (key_event->keyval == 'd'){
			this->body->SetLinearVelocity(b2Vec2(100, 0));
			std::this_thread::sleep_for (std::chrono::milliseconds(15));
			this->body->SetLinearVelocity(b2Vec2(0, 0));
			return true;
		}
		if (key_event->keyval == 'w'){
			this->body->SetLinearVelocity(b2Vec2(0, -100));
			std::this_thread::sleep_for (std::chrono::milliseconds(15));
			this->body->SetLinearVelocity(b2Vec2(0, 0));
			return true;
		}
		if (key_event->keyval == 's'){
			this->body->SetLinearVelocity(b2Vec2(0, 100));
			std::this_thread::sleep_for (std::chrono::milliseconds(15));
			this->body->SetLinearVelocity(b2Vec2(0, 0));
			return true;
		}
		//this->body->SetLinearVelocity(b2Vec2(10, 0));
		return true;

	}
};

class MyWorld: public Thread{
public:
	b2World* world;
	b2Body* staticBody;
	UserData data;
	CollisionListener colission;

	MyWorld(){
	

		world = new b2World(b2Vec2(0.0f, 0.0));
		world->SetAllowSleeping(true);
		world->SetContinuousPhysics(true);
		world->SetContactListener(&colission);

		//Viga en el piso
		
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody; //this will be a static body
		myBodyDef.position.Set(0, 900); //slightly lower position
		staticBody = this->world->CreateBody(&myBodyDef); //add body to world

		data.setDatos("Viga", this->staticBody);
		staticBody->SetUserData(&data);


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
			float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
			  int32 velocityIterations = 8;   //how strongly to correct velocity
			  int32 positionIterations = 3;   //how strongly to correct position
			  std::this_thread::sleep_for (std::chrono::milliseconds(15));
			  this->world->Step( timeStep, velocityIterations, positionIterations);
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
	std::mutex mutex;
    auto app = Gtk::Application::create(argc, argv);
    Gtk::Window ventana;
    Gtk::Fixed world_map;
    Gtk::ScrolledWindow map;
    map.add(world_map);
    //map.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
	Gtk::Button buttonQuit;
    ventana.resize(1000, 1000);
	Gtk::Image bomba;
	bomba.set("resources/images/1.png");
	world_map.put(bomba,300, 500);
	
	for (int i = 1; i <= 15; i++) 
		cola.push("resources/images/" + std::to_string(i) + ".png");

	Gtk::Image bomba2;
	bomba2.set("resources/images/bomba2.png");
	world_map.put(bomba2,600, 500);
	
	buttonQuit.add_label("Quit");
	buttonQuit.signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app));
	
	world_map.put(buttonQuit,300, 300);
	ventana.add(map);
    ventana.show_all();

    Imagen imagen(bomba, world_map, 300, true, mutex);
    Imagen imagen2(bomba2, world_map, 400, false, mutex);
    MyWorld w;
    w.add_imagen(imagen);
    w.add_imagen(imagen2);
    w.start();
    imagen.start();
    imagen2.start();
    app->run(ventana);
    imagen.stop();
    imagen.join();
    imagen2.stop();
    imagen2.join();
    w.stop();
    w.join();
	return 0;
}

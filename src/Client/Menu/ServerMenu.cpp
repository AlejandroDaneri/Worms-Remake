#include "ServerMenu.h"
#include "Path.h"
#include <gtkmm/builder.h>

ServerMenu::ServerMenu(Gtk::Window& window): window(window){
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_ServerMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("host", this->host);
	builder->get_widget("service", this->service);
	builder->get_widget("connect", this->connect);

	Gtk::Box* menu;
	builder->get_widget("server_menu", menu);
	this->window.add(*menu);
	menu->show();

	this->connect->signal_clicked().connect(sigc::mem_fun(*this, &ServerMenu::connect_button_pressed));
}

ServerMenu::~ServerMenu(){}

void ServerMenu::connect_button_pressed(){
	std::string host(this->host->get_text());
	if (host.empty()){
		this->error->set_label("Debe ingresar un host");
		return;
	}

	std::string service(this->service->get_text());
	if (service.empty()){
		this->error->set_label("Debe ingresar un servicio");
		return;
	}

	this->connect_to_server(host, service);
}

void ServerMenu::connect_to_server(const std::string& host, const std::string& service){
	try{
		Socket socket(Socket::Client(host.c_str(), service.c_str()));
		ClientProtocol protocol(std::move(socket));
		this->window.remove();
		this->game_menu = std::unique_ptr<GameMenu>(new GameMenu(this->window, std::move(protocol)));
	} catch (const SocketException& e){
		this->error->set_label("No pudo conectarse al servidor");
	}
}

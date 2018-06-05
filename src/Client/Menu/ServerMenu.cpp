#include "ServerMenu.h"
#include <gtkmm/builder.h>
#include "Path.h"
#include "ButtonBuilder.h"

ServerMenu::ServerMenu(Gtk::Window& window): window(window) {
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_ServerMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("host", this->host);
	builder->get_widget("service", this->service);
	builder->get_widget("connect", this->connect);
	builder->get_widget("quit_game", this->quit);

	ButtonBuilder::buildButton(this->quit);
	ButtonBuilder::buildButton(this->connect);

	builder->get_widget("server_menu", this->menu);

	builder->get_widget("background", this->background);
	Glib::RefPtr<Gdk::Pixbuf> aux = Gdk::Pixbuf::create_from_file(BACKGROUND_MENU_IMAGE);
	this->background->set(aux);

	this->window.add(*this->menu);
	this->window.show_all();

	this->connect->signal_clicked().connect(sigc::mem_fun(*this, &ServerMenu::connectButtonPressed));
	this->quit->signal_clicked().connect(sigc::mem_fun(*this, &ServerMenu::quitButtonPressed));
}

ServerMenu::~ServerMenu(){
	delete this->menu;
}

void ServerMenu::connectButtonPressed(){
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

    this->connectToServer(host, service);
}

void ServerMenu::quitButtonPressed() {
	this->window.close();
}

void ServerMenu::connectToServer(const std::string &host, const std::string &service){
	try{
		Socket socket(Socket::Client(host.c_str(), service.c_str()));
		this->protocol.reset(new ClientProtocol(std::move(socket), this->window));
		this->window.remove();
		this->next_menu = std::unique_ptr<MenuView>(new GameMenu(this->window, *this->protocol));
	} catch (const SocketException& e){
		this->error->set_label("No pudo conectarse al servidor");
	}
}

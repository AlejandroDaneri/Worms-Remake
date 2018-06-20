#include "ServerMenu.h"
#include <string>
#include "Path.h"
#include "ButtonBuilder.h"

const std::string PATH = GLADE_PATH + "client_ServerMenu.glade";

ServerMenu::ServerMenu(Gtk::Window& window) : Menu(PATH, window) {
	this->builder->get_widget("host", this->host);
	this->builder->get_widget("service", this->service);
	this->builder->get_widget("connect", this->connect);

	ButtonBuilder::buildButton(this->connect);

	this->builder->get_widget("server_menu", this->menu);

	this->window.add(*this->menu);
	this->window.show_all();

	this->hideWarningBox();

	this->connect->signal_clicked().connect(
			sigc::mem_fun(*this, &ServerMenu::connectButtonPressed));
}

ServerMenu::~ServerMenu() {
	delete this->menu;
}

void ServerMenu::connectButtonPressed() {
	std::string host(this->host->get_text());
	if (host.empty()) {
		this->showError("Debe ingresar un host");
		return;
	}

	std::string service(this->service->get_text());
	if (service.empty()) {
		this->showError("Debe ingresar un servicio");
		return;
	}

	this->connectToServer(host, service);
}

void ServerMenu::connectToServer(const std::string& host,
								 const std::string& service) {
	try {
		Socket socket(Socket::Client(host.c_str(), service.c_str()));
		this->protocol.reset(
				new ClientProtocol(std::move(socket), this->window));
		this->window.remove();
		this->next_menu = std::unique_ptr<MenuView>(
				new GameMenu(this->window, *this->protocol));
	} catch(const SocketException& e) {
		this->showError("No pudo conectarse al servidor");
	}
}

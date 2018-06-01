#include "SelectableListMenu.h"

SelectableListMenu::SelectableListMenu(Gtk::Window& window, MenuView& first_menu, ClientProtocol& protocol, std::string&& name):
	MenuView(window, first_menu, protocol), player_name(std::move(name)){}

SelectableListMenu::~SelectableListMenu(){}

void SelectableListMenu::configure(int quantity){
	try{
		for (int i = 0; i < quantity; i++){
			std::string field = this->protocol.receiveString();
			this->addField(field);
		}
	}catch (const SocketException& e){
        this->showFatalError();
	}

	for (auto it = this->fields.begin(); it != this->fields.end(); ++it){
		this->games->pack_start(it->getContainer());
	}
	this->games->show();
}

void SelectableListMenu::addField(const std::string& field_name){
	GameMenuField field(field_name);
	this->fields.push_back(std::move(field));
	this->fields.back().getButton().signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this,
                                                                                                   &SelectableListMenu::selectButtonPressed), field_name));
}

bool SelectableListMenu::createPlayer(){
	try{
		this->player = std::unique_ptr<Player>(new Player(std::move(this->protocol), this->player_name, this->window));
	} catch (const std::exception& e){
        this->showFatalError();
	}
	return false;
}

void SelectableListMenu::waitToPlayers(){
	this->window.remove();
	this->window.add(this->waiting_label.getWidget());
	this->window.show_all();
	sigc::slot<bool> my_slot = sigc::mem_fun(*this, &SelectableListMenu::createPlayer);
	Glib::signal_idle().connect(my_slot);
}

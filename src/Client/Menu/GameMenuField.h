#ifndef __GAMEMENUFIELD_H__
#define __GAMEMENUFIELD_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <string>

class GameMenuField{
	private:
		Gtk::Label title;
		Gtk::Button button;
		Gtk::HBox container;

	public:
		GameMenuField(const std::string& title);
		~GameMenuField();

		GameMenuField(GameMenuField&& other);

		Gtk::Container& getContainer();

		Gtk::Button& getButton();
};


#endif

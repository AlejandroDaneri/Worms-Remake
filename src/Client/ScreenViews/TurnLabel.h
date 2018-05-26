#ifndef __TURNLABEL_H__
#define __TURNLABEL_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>

class TurnLabel{
	private:
		Gtk::Label message;
		Gtk::Label time;
		Gtk::HBox label;

	public:
		TurnLabel();
		~TurnLabel();

		void beginTurn();

		void beginTurn(const std::string& player_name);

		void endTurn();

		void setTime(int time);
		
		Gtk::Container& getWindow();

		bool setLabelCallback(std::string text);
};


#endif

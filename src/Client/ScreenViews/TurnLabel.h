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

		void endTurn();

		void setTime(int time);
		
		Gtk::Container& getWindow();
};


#endif

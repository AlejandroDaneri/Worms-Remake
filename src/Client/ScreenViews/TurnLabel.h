#ifndef __TURNLABEL_H__
#define __TURNLABEL_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>

class TurnLabel{
	private:
		Gtk::Label label;

	public:
		TurnLabel();
		~TurnLabel();

		void beginTurn();
		
		Gtk::Label& getWindow();
};


#endif

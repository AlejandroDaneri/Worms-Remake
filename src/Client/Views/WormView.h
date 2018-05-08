#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__

#include "Viewable.h"
#include <gtkmm/widget.h>
#include <gtkmm/image.h>

#define DIR_RIGHT 0
#define DIR_LEFT 1


class WormView: public Viewable{
	private:
		int life;
		char dir;
		bool dir_changed;
		Gtk::Image image; ////////////////////////////////////Cambiar por vbox para agegar barra de vida

	protected:
		Gtk::Widget& getWidget() override;

	public:
		WormView(WorldView& worldView, int life, char dir, Position pos);
		~WormView();

		void updateData(int new_life, char new_dir, const Position& new_pos);

		void kill();

		WormView(WormView&& other);

};


#endif

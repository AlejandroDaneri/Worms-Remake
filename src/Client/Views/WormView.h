#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__

#include "Viewable.h"
#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <gtkmm/grid.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/label.h>
#include <queue>

#define DIR_RIGHT 1
#define DIR_LEFT -1


class WormView: public Viewable{
	private:
		int player_id;
		int life;
		char dir;
		bool dir_changed;
		std::string weapon;
		//std::queue<Glib::RefPtr<Gdk::Pixbuf>> queue;
		//Glib::RefPtr<Gdk::Pixbuf> full_image;
		Gtk::Label label;
		Gtk::Image image;
		Gtk::Grid worm;

	public:
		WormView(WorldView& worldView, int life, char dir, Position pos, int player_id, const std::string& weapon);
		~WormView();
		WormView(WormView&& other);

		void updateData(int new_life, char new_dir, const Position& new_pos, const std::string& weapon);

		const char getDir() const;

		void kill();
		
		Gtk::Widget& getWidget() override;
};


#endif

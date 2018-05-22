#ifndef __CLIENTBULLETVIEW_H__
#define __CLIENTBULLETVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <string>
#include "Viewable.h"

class BulletView: public Viewable{
	private:
		Gtk::Image image;
		std::string weapon_name;
		//std::vector<Glib::RefPtr<Gdk::Pixbuf>> animation_vector;
		//Glib::RefPtr<Gdk::Pixbuf> animation;

	public:
		BulletView(WorldView& worldView, std::string weapon, Position pos);
		~BulletView();
		BulletView(BulletView&& other);

		void updateData(const Position& new_pos);

		void explode();
		
		Gtk::Widget& getWidget() override;
};


#endif

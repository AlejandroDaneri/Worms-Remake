#ifndef __CLIENTBULLETVIEW_H__
#define __CLIENTBULLETVIEW_H__

#include "Viewable.h"
#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <string>

class BulletView: public Viewable{
	private:
		Gtk::Image image;
		std::string weapon_name;

	protected:
		Gtk::Widget& getWidget() override;

	public:
		BulletView(WorldView& worldView, std::string weapon, Position pos);
		~BulletView();
		BulletView(BulletView&& other);

		void updateData(const Position& new_pos);

		void explode();
};


#endif

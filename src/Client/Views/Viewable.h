#ifndef __VIEWABLE_H__
#define __VIEWABLE_H__

#include "WorldView.h"
#include "Position.h"
#include <gtkmm/widget.h>

#define IMAGES_PATH "resources/images/"

class Viewable{
	private:
		WorldView& worldView;

	protected:
		void addToWorld(const Position& pos);

		void removeFromWorld();

		void move(const Position& pos);

	public:
		Viewable(WorldView& worldView);
		virtual ~Viewable();

		Viewable(Viewable&& other);
		
		virtual Gtk::Widget& getWidget() = 0;
};

#endif

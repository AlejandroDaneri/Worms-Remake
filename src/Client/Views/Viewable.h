#ifndef __VIEWABLE_H__
#define __VIEWABLE_H__

#include "WorldView.h"
#include "Position.h"
#include <gtkmm/widget.h>

#define IMAGES_PATH "resources/images/"

class Viewable{
	private:
		WorldView& worldView;
		bool has_focus;

	protected:
		void addToWorld(const Position& pos, float width, float height);

		void removeFromWorld();

		void move(const Position& pos, float width, float height);

	public:
		Viewable(WorldView& worldView);
		virtual ~Viewable();

		Viewable(Viewable&& other);
		
		virtual Gtk::Widget& getWidget() = 0;

		void setFocus(bool focus);

		bool hasFocus() const;
};

#endif

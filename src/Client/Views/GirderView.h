#ifndef __GIRDERVIEW_H__
#define __GIRDERVIEW_H__

#include "Viewable.h"
#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <string>

class GirderView: public Viewable{
	private:
		Gtk::Image image;
		std::string girder_name;

	protected:
		Gtk::Widget& getWidget() override;

	public:
		GirderView(WorldView& worldView, std::string girder, Position pos);
		~GirderView();
		GirderView(GirderView&& other);

		void updateData(const Position& new_pos);

		void explode();
};


#endif

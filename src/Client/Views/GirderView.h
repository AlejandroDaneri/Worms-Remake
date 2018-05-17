#ifndef __GIRDERVIEW_H__
#define __GIRDERVIEW_H__

#include "Viewable.h"
#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <string>

class GirderView: public Viewable{
	private:
		Gtk::Image image;
		int size;
		int rotation;

	protected:


	public:
		GirderView(WorldView& worldView, size_t size, Position pos, int rotation);
		~GirderView();
		GirderView(GirderView&& other);
		
		Gtk::Widget& getWidget() override;
};


#endif

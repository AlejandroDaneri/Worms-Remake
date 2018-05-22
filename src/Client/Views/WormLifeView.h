#ifndef __WORMLIFEVIEW_H__
#define __WORMLIFEVIEW_H__

#include <gtkmm/label.h>

class WormLifeView{
	private:
		Gtk::Label label;

	public:
		WormLifeView(int life);
		~WormLifeView();
		WormLifeView(WormLifeView&& other);

		void updateLife(int life);
		
		Gtk::Widget& getWidget();
};


#endif

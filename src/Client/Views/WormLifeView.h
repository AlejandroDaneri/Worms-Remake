#ifndef __WORMLIFEVIEW_H__
#define __WORMLIFEVIEW_H__

#include <gtkmm/label.h>

class WormLifeView{
	private:
		Gtk::Label label;
		std::string color;

	public:
		WormLifeView(int life, const std::string& color);
		~WormLifeView();
		WormLifeView(WormLifeView&& other);

		void updateLife(int life);
		
		Gtk::Widget& getWidget();
};


#endif

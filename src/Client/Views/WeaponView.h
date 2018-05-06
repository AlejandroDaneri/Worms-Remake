#ifndef __WEAPONVIEW_H__
#define __WEAPONVIEW_H__

#include "Viewable.h"
#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <string>

class WeaponView: public Viewable{
	private:
		Gtk::Image image;
		std::string weapon_name;

	protected:
		Gtk::Widget& getWidget() override;

	public:
		WeaponView(WorldView& worldView, std::string weapon, Position pos);
		~WeaponView();

		void updateData(const Position& new_pos);

		void explode();

		WeaponView(WeaponView&& other);

};


#endif

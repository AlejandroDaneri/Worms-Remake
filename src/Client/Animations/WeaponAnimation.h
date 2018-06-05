#ifndef WORMS_WEAPONANIMATION_H
#define WORMS_WEAPONANIMATION_H

#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <vector>
#include <string>

class WormView;

class WeaponAnimation {
	private:
		std::vector<Glib::RefPtr<Gdk::Pixbuf>> scope_vector;
		Glib::RefPtr<Gdk::Pixbuf> scope_image;
		Gtk::Image* worm_image;
		int angle;


		void updateWeaponImage(const std::string& weapon);

		/* Callback */
		bool batHitCallBack(std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator& iter, const int width, char dir);

	public:
		WeaponAnimation(const std::string& weapon, Gtk::Image* worm_image);
		~WeaponAnimation();
		WeaponAnimation(WeaponAnimation&& other);

		void changeWeapon(const std::string& weapon, char dir);

		void setWeaponImage(char dir);

		/* Realiza la animacion del worm bateando */
		void weaponShootAnimation(const std::string &weapon, char dir);

		void changeAngle(int angle, char dir);

		void updateWormImage(Gtk::Image* worm_image);
};


#endif //WORMS_WEAPONANIMATION_H

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
		WormView* wormView;
		int angle;

		void updateWeaponImage(const std::string& weapon);

		/* Callback */
		bool batHitCallBack(std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator& iter, const int width);

	public:
		WeaponAnimation(const std::string& weapon, WormView* wormView);
		~WeaponAnimation();
		WeaponAnimation(WeaponAnimation&& other);

		void changeWeapon(const std::string& weapon);

		void setWeaponImage();

		/* Realiza la animacion del worm bateando */
		void batHit();

		void changeAngle(int angle);

		void updateWormView(WormView* wormView);
};


#endif //WORMS_WEAPONANIMATION_H

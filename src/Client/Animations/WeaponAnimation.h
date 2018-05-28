#ifndef WORMS_WEAPONANIMATION_H
#define WORMS_WEAPONANIMATION_H

#include <vector>
#include <string>
#include <gdkmm/pixbuf.h>

class WormView;

class WeaponAnimation {
    private:
        WormView& wormView;
        std::vector<Glib::RefPtr<Gdk::Pixbuf>> animation_vector;
        Glib::RefPtr<Gdk::Pixbuf> animation;
        std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator iter;

        bool startCallBack(int dir);

    public:
        WeaponAnimation(WormView& wormView, std::string weapon);
        ~WeaponAnimation();

        WeaponAnimation(WeaponAnimation&& other);

        void changeWeapon(std::string weapon);

        void start(int dir);

        bool hasFinished();
};


#endif //WORMS_WEAPONANIMATION_H

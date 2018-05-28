#include "WeaponAnimation.h"
#include <glibmm/main.h>
#include <thread>
#include "ObjectSizes.h"
#include "Path.h"
#include "WormView.h"


#include <iostream>//////////////////////////

WeaponAnimation::WeaponAnimation(WormView& wormView, std::string weapon) :
    wormView(wormView) {
    this->changeWeapon(weapon);
}

WeaponAnimation::~WeaponAnimation() {}

WeaponAnimation::WeaponAnimation(WeaponAnimation&& other) : wormView(other.wormView),
    animation_vector(std::move(other.animation_vector)),
    animation(std::move(other.animation)) {
}

void WeaponAnimation::changeWeapon(std::string weapon) {
    this->animation_vector.clear();
    this->animation = Gdk::Pixbuf::create_from_file(ANIMATIONS_PATH + weapon + "_animation.png");

    std::cout << "Path = " << ANIMATIONS_PATH + weapon + "_animation.png" << std::endl;

    int width = this->animation->get_width();
    int height = this->animation->get_height();
    std::cout << "ancho = " << width << " alto = " << height << std::endl;
    for (int i = 0; i < height/WORM_IMAGE_WIDTH; i++) {
        Glib::RefPtr<Gdk::Pixbuf> aux = Gdk::Pixbuf::create_subpixbuf(this->animation, 0, i * WORM_IMAGE_WIDTH, width, WORM_IMAGE_WIDTH);
        this->animation_vector.push_back(std::move(aux));
        std::cout << "pos_y = " << i * WORM_IMAGE_WIDTH << std::endl;
    }

    std::cout << "Size = " << this->animation_vector.size() << std::endl;
}


/*bool WeaponAnimation::startCallBack(int dir) {
    if (iter == this->animation_vector.end()) {
        return false;
    }
    Gtk::Image& image = this->wormView.getImage();
    image.set(Gdk::Pixbuf::create_subpixbuf(*(this->iter),WORM_IMAGE_WIDTH + dir * WORM_IMAGE_WIDTH, 0, WORM_IMAGE_WIDTH, WORM_IMAGE_WIDTH));
    this->iter++;
    return true;
}

void WeaponAnimation::start(int dir) {
    this->iter = this->animation_vector.begin();
    sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &WeaponAnimation::startCallBack), dir);
    Glib::signal_timeout().connect(my_slot, 40);
}*/

void WeaponAnimation::start(int dir) {
    std::cout << "dir = " << dir << std::endl;
    std::cout << "Start Size = " << this->animation_vector.size() << std::endl;
    std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator iter;
    iter = this->animation_vector.begin();

    while (iter != this->animation_vector.end()) {
        std::cout << "Antes de setear image" << std::endl;
        this->wormView.getImage().set(Gdk::Pixbuf::create_subpixbuf(*iter, WORM_IMAGE_WIDTH + dir * WORM_IMAGE_WIDTH, 0, WORM_IMAGE_WIDTH, WORM_IMAGE_WIDTH));
        iter++;
        std::cout << "Antes del sleep" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

bool WeaponAnimation::hasFinished() {
    return this->iter == this->animation_vector.end();
    //return true;
}

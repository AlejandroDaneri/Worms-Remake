#include "WeaponAnimation.h"
#include <glibmm/main.h>
#include "WormView.h"
#include "Path.h"
#include "ObjectSizes.h"
#include "WeaponNames.h"

#define DIR_RIGHT 1

WeaponAnimation::WeaponAnimation(const std::string& weapon, WormView* wormView) :
	wormView(wormView),	angle(DEFAULT_ANGLE) {
	this->updateWeaponImage(weapon);
}

WeaponAnimation::~WeaponAnimation() {}

WeaponAnimation::WeaponAnimation(WeaponAnimation&& other) :
	scope_vector(std::move(other.scope_vector)),
	scope_image(std::move(other.scope_image)), wormView(std::move(other.wormView)),
	angle(other.angle) {}

void WeaponAnimation::updateWeaponImage(const std::string& weapon) {
	this->scope_vector.clear();
	this->scope_image = Gdk::Pixbuf::create_from_file(WORMS_PATH + weapon + "_scope.png");
	int width = this->scope_image->get_width();
	int height = this->scope_image->get_height();
	for (int i = 0; i < height / WORM_IMAGE_WIDTH; i++) {
		this->scope_vector.push_back(Gdk::Pixbuf::create_subpixbuf(scope_image, 0, i * WORM_IMAGE_WIDTH, width, WORM_IMAGE_WIDTH));
	}
}

void WeaponAnimation::changeWeapon(const std::string& weapon) {
	this->updateWeaponImage(weapon);
	this->setWeaponImage();
}

void WeaponAnimation::setWeaponImage() {
	Glib::RefPtr<Gdk::Pixbuf> aux = this->scope_vector[(90 + this->angle) / 6];
	int width = aux->get_width() / 3;
	int height = aux->get_height();
	char dir = this->wormView->getDir();
	this->wormView->getImage().set(Gdk::Pixbuf::create_subpixbuf(aux, width + dir * width, 0, width, height));
}

bool WeaponAnimation::batHitCallBack(std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator& iter, const int width) {
	this->wormView->getImage().set(Gdk::Pixbuf::create_subpixbuf(*iter, 0, 0, width, WORM_IMAGE_WIDTH));
	iter++;
	if (iter == this->scope_vector.end()) {
		this->changeWeapon(BAT_NAME);
		this->wormView->setStaticImage();
		return false;
	}
	return true;
}

void WeaponAnimation::batHit() {
	char dir = this->wormView->getDir();
	this->scope_image = Gdk::Pixbuf::create_from_file(BAT_HIT_ANIMATION);
	int width = this->scope_image->get_width() / 3;
	int height = this->scope_image->get_height();
	int pos_x = width + dir * width;
	this->scope_vector.clear();
	for (int i = 0; i < height / WORM_IMAGE_WIDTH; i++) {
		this->scope_vector.push_back(Gdk::Pixbuf::create_subpixbuf(scope_image, pos_x, i * WORM_IMAGE_WIDTH, width, WORM_IMAGE_WIDTH));
	}
	std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator iter = this->scope_vector.begin();
	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &WeaponAnimation::batHitCallBack), iter, width);
	Glib::signal_timeout().connect(my_slot, 12);
}

void WeaponAnimation::changeAngle(int angle) {
	this->angle = angle;
}

void WeaponAnimation::updateWormView(WormView* wormView) {
	this->wormView = wormView;
}

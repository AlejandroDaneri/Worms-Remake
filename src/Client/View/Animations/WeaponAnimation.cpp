#include "WeaponAnimation.h"
#include <glibmm/main.h>
#include <string>
#include <vector>
#include "WormView.h"
#include "Path.h"
#include "ObjectSizes.h"
#include "WeaponNames.h"

#define DIR_RIGHT 1

WeaponAnimation::WeaponAnimation(const std::string& weapon,
								 Gtk::Image* worm_image) :
		worm_image(worm_image), angle(DEFAULT_ANGLE) {
	this->updateWeaponImage(weapon);
}

WeaponAnimation::~WeaponAnimation() {
	if (this->my_connection.connected()) {
		this->my_connection.disconnect();
	}
}

WeaponAnimation::WeaponAnimation(WeaponAnimation&& other) :
		scope_vector(std::move(other.scope_vector)),
		scope_image(std::move(other.scope_image)),
		worm_image(other.worm_image),
		angle(other.angle) {}

void WeaponAnimation::updateWeaponImage(const std::string& weapon) {
	this->scope_vector.clear();
	this->scope_image = Gdk::Pixbuf::create_from_file(
			WORMS_PATH + weapon + "_scope.png");
	int width = this->scope_image->get_width();
	int height = this->scope_image->get_height();
	for (int i = 0; i < height / WORM_IMAGE_WIDTH; i++) {
		this->scope_vector.push_back(
				Gdk::Pixbuf::create_subpixbuf(scope_image, 0,
											  i * WORM_IMAGE_WIDTH, width,
											  WORM_IMAGE_WIDTH));
	}
}

void WeaponAnimation::changeWeapon(const std::string& weapon, char dir) {
	this->updateWeaponImage(weapon);
	this->setWeaponImage(dir);
}

void WeaponAnimation::setWeaponImage(char dir) {
	int width = this->scope_vector[(90 + this->angle) / 6]->get_width() / 3;
	int height = this->scope_vector[(90 + this->angle) / 6]->get_height();
	this->worm_image->set(Gdk::Pixbuf::create_subpixbuf(
			this->scope_vector[(90 + this->angle) / 6], width + dir * width, 0,
			width, height));
}

bool WeaponAnimation::batHitCallBack(
		std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator& iter, const int width,
		char dir) {
	this->worm_image->set(Gdk::Pixbuf::create_subpixbuf(*iter, 0, 0, width,
														WORM_IMAGE_WIDTH));
	++iter;
	if (iter == this->scope_vector.end()) {
		this->updateWeaponImage(BAT_NAME);
		this->setWeaponImage(dir);
		return false;
	}
	return true;
}

void WeaponAnimation::weaponShootAnimation(const std::string& weapon, char dir){
	if (weapon != BAT_NAME) {
		return;
	}
	this->scope_image = Gdk::Pixbuf::create_from_file(BAT_HIT_ANIMATION);
	int width = this->scope_image->get_width() / 3;
	int height = this->scope_image->get_height();
	int pos_x = width + dir * width;
	this->scope_vector.clear();
	for (int i = 0; i < height / WORM_IMAGE_WIDTH; i++) {
		this->scope_vector.push_back(
				Gdk::Pixbuf::create_subpixbuf(scope_image, pos_x,
								i * WORM_IMAGE_WIDTH, width, WORM_IMAGE_WIDTH));
	}
	std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator iter;
	iter = this->scope_vector.begin();
	sigc::slot<bool> my_slot = sigc::bind(
			sigc::mem_fun(*this, &WeaponAnimation::batHitCallBack), iter, width,
			dir);
	this->my_connection = Glib::signal_timeout().connect(my_slot, 12);
}

void WeaponAnimation::changeAngle(int angle, char dir) {
	this->angle = angle;
	this->setWeaponImage(dir);
}

void WeaponAnimation::updateWormImage(Gtk::Image* worm_image) {
	this->worm_image = worm_image;
}

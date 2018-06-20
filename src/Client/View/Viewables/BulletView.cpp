#include "BulletView.h"
#include <string>
#include "ObjectSizes.h"

BulletView::BulletView(WorldView& worldView, std::string weapon, Position pos) :
		Viewable(worldView), weapon_name(std::move(weapon)) {
	std::string path(BULLETS_PATH);
	path += this->weapon_name;
	path += ".png";
	this->image.set(path);
	this->addToWorld(pos);
}

BulletView::~BulletView() {}

BulletView::BulletView(BulletView&& other) :
		Viewable(std::move(other)), image(std::move(other.image)),
		weapon_name(std::move(other.weapon_name)) {}

void BulletView::updateData(const Position& new_pos) {
	this->move(new_pos);
}

Gtk::Widget& BulletView::getWidget() {
	return this->image;
}

float BulletView::getWidth() const {
	return weapon_size;
}

float BulletView::getHeight() const {
	return weapon_size;
}

std::string BulletView::getName() {
	return this->weapon_name;
}

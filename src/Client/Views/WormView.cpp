#include "WormView.h"
#include <string>
#include <glibmm/main.h>
#include "ObjectSizes.h"
#include "WeaponNames.h"
#include "GamePlayers.h"

WormView::WormView(WorldView& worldView, int life, char dir, Position pos, int player_id):
	Viewable(worldView), player_id(player_id), life(life), is_moving(false),
	last_position(Position(-1, -1)), label(life, colors[player_id]),
	walkingAnimation(&this->image), weaponAnimation(DEFAULT_WEAPON, &this->image) {
		this->worm.attach(this->label.getWidget(), 0, 0, 1, 1);
		this->worm.attach(this->image, 0, 1, 1, 1);
		this->walkingAnimation.setStaticImage();
		this->addToWorld(pos, worm_size, worm_size + 0.5);
}

WormView::~WormView(){}
	
WormView::WormView(WormView&& other): Viewable(std::move(other)), player_id(other.player_id),
	life(other.life), is_moving(other.is_moving),
	last_position(other.last_position), label(std::move(other.label)),
	image(std::move(other.image)),
    worm(std::move(other.worm)), walkingAnimation(std::move(other.walkingAnimation)),
    weaponAnimation(std::move(other.weaponAnimation)) {
	this->weaponAnimation.updateWormImage(&this->image);
	this->walkingAnimation.updateWormImage(&this->image);
}

void WormView::updateData(int new_life, char new_dir, const Position& new_pos, bool colliding, bool is_current_worm, bool has_shot) {
	if (new_life != this->life){
		this->label.updateLife(new_life);
	}
	this->life = new_life;
	this->is_moving = !(this->last_position == new_pos);
	this->last_position = new_pos;
	this->setNewImage(new_dir, colliding, is_current_worm, has_shot);
	this->move(new_pos, worm_size, worm_size + 0.5);
}

void WormView::updateScope(int angle) {
    this->weaponAnimation.changeAngle(angle, this->getDir());
}

void WormView::changeWeapon(const std::string& weapon) {
	this->weaponAnimation.changeWeapon(weapon, this->getDir());
}

void WormView::setNewImage(char dir, bool colliding, bool is_current_worm, bool has_shot){
	if (is_current_worm){
		if (!this->is_moving && !has_shot){
			this->weaponAnimation.setWeaponImage(dir);
		} else if (colliding){
			this->walkingAnimation.setMovementImage(dir);
		}
		return;
	}
	this->walkingAnimation.setStaticImage();
}

Gtk::Widget& WormView::getWidget(){
	return this->worm;
}

Gtk::Image& WormView::getImage() {
    return this->image;
}

int WormView::getLife() const{
	return this->life;
}

char WormView::getDir() const {
	return this->walkingAnimation.getDir();
}

int WormView::getPlayerId() const{
	return this->player_id;
}

bool WormView::isMoving() const{
	return this->is_moving;
}

void WormView::setVictory() {
    this->image.set(VICTORY_ANIMATION);
}

void WormView::weaponShoot(const std::string& weapon) {
	this->weaponAnimation.weaponShootAnimation(weapon, this->getDir());
}

void WormView::resetFocus(){
	this->is_moving = false;
	this->setFocus(false);
	this->walkingAnimation.setStaticImage();
}

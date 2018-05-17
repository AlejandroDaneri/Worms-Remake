#include "client_BulletView.h"

#define BULLETS_PATH "bullets/"

BulletView::BulletView(WorldView& worldView, std::string weapon, Position pos):
	Viewable(worldView), weapon_name(std::move(weapon)){

	std::string path(IMAGES_PATH);///////////////por ahora es mas eficiente porque es solo una imagen
	path += BULLETS_PATH;
	path += this->weapon_name;
	path += ".png";
	this->image.set(path);
	this->addToWorld(pos);
}

BulletView::~BulletView(){}

void BulletView::updateData(const Position& new_pos){
	this->move(new_pos);
}

void BulletView::explode(){
	this->removeFromWorld();
	////////////////////////////////////////Hacer sonido de explosion y animacion? Si se hace animacion hay que guardar la ultima posicion del arma
}

Gtk::Widget& BulletView::getWidget(){
	////////////////////////////////////////////Ver que hacer con la rotacion, por ahora lo dejo asi
	/*std::string path(IMAGES_PATH);
	path += this->weapon_name;
	path += ".png";
	this->image.set(path);*/
	return this->image;
}

BulletView::BulletView(BulletView&& other): Viewable(std::move(other)),
	image(std::move(other.image)), weapon_name(std::move(other.weapon_name)){}

#include "PlayerLifeLabel.h"

const std::string begining("<span size='13000'>  ");
const std::string ending("</span>");

PlayerLifeLabel::PlayerLifeLabel(): life(0){
	this->label.set_use_markup(true);
}

PlayerLifeLabel::~PlayerLifeLabel(){}

void PlayerLifeLabel::setPlayerName(const std::string& player_name){
	this->player_name = player_name;
	this->updateLabel();
}

void PlayerLifeLabel::addLife(int life){
	this->life += life;
	this->updateLabel();
}

void PlayerLifeLabel::reduceLife(int life){
	this->life -= life;
	this->updateLabel();
}
		
Gtk::Label& PlayerLifeLabel::getLabel(){
	return this->label;
}

void PlayerLifeLabel::updateLabel(){
	this->label.set_markup(begining + this->player_name + "\nVida total: " + std::to_string(this->life) + ending);
}

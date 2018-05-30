#include "PlayerLifeLabel.h"
#include "GamePlayers.h"

const std::string begining("<span color='");
const std::string middle("'>");
const std::string ending("</span>");

PlayerLifeLabel::PlayerLifeLabel(): id(0), player_name(""), life(0){
	this->label.set_use_markup(true);
}

PlayerLifeLabel::~PlayerLifeLabel(){}

void PlayerLifeLabel::setPlayerName(int id, const std::string& player_name){
	this->id = id;
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
	std::string message = begining + colors[this->id] + middle;
	message += std::to_string(this->id) + "- " + this->player_name;
	message += ": " + std::to_string(this->life) + ending;
	this->label.set_markup(message);
}

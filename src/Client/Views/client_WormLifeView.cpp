#include "WormLifeView.h"

const std::string begining("<span color='red'><b>");
const std::string ending("</b></span>");

WormLifeView::WormLifeView(int life){
	this->label.set_use_markup(true);
	this->updateLife(life);
}

WormLifeView::~WormLifeView(){}

WormLifeView::WormLifeView(WormLifeView&& other): label(std::move(other.label)){}

void WormLifeView::updateLife(int life){
	this->label.set_markup(begining + std::to_string(life) + ending);
}
		
Gtk::Widget& WormLifeView::getWidget(){
	return this->label;
}
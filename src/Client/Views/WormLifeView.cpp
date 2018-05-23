#include "WormLifeView.h"

const std::string begining("<span color='");
const std::string middle("'><b>");
const std::string ending("</b></span>");

WormLifeView::WormLifeView(int life, const std::string& color): color(color){
	this->label.set_use_markup(true);
	this->updateLife(life);
}

WormLifeView::~WormLifeView(){}

WormLifeView::WormLifeView(WormLifeView&& other):
	label(std::move(other.label)), color(std::move(other.color)){}

void WormLifeView::updateLife(int life){
	this->label.set_markup(begining + this->color + middle + std::to_string(life) + ending);
}
		
Gtk::Widget& WormLifeView::getWidget(){
	return this->label;
}
#include "WaitingLabel.h"
#include <string>

const std::string begining("<span size='20000'>");
const std::string ending("</span>");

WaitingLabel::WaitingLabel() {
	this->label.set_use_markup(true);
	this->label.set_markup(begining + "Esperando jugadores..." + ending);
	this->label.show();
}

WaitingLabel::~WaitingLabel() {}

Gtk::Widget& WaitingLabel::getWidget() {
	return this->label;
}

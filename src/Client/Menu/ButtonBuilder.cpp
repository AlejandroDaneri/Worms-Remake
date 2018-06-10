#include "ButtonBuilder.h"
#include <string>
#include <gtkmm/label.h>
#include <gdkmm/rgba.h>

void ButtonBuilder::buildButton(Gtk::Button* button) {
	std::string text = button->get_label();
	Gtk::Label* label = (Gtk::Label*) button->get_child();
	label->set_markup("<b>" + text + "</b>");
	label->override_color(Gdk::RGBA("black"));
}

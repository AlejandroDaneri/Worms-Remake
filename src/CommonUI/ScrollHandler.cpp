#include "ScrollHandler.h"
#include <gtkmm/adjustment.h>
#include <glibmm/main.h>

#define SPACE_TO_SCROLL 10
#define SCROLL_INCREMENT 25

ScrollHandler::ScrollHandler(Gtk::ScrolledWindow& window): window(window), last_mouse_position(SPACE_TO_SCROLL * 2, SPACE_TO_SCROLL * 2), mouse_in_window(false){
	this->window.add_events(Gdk::POINTER_MOTION_MASK);
	this->window.add_events(Gdk::ENTER_NOTIFY_MASK);
	this->window.add_events(Gdk::ENTER_NOTIFY_MASK);
	this->window.signal_motion_notify_event().connect(sigc::mem_fun(*this, &ScrollHandler::mouseMotionEvent));
	this->window.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);

	this->window.signal_enter_notify_event().connect(sigc::mem_fun(*this, &ScrollHandler::mouseEntered));
	this->window.signal_leave_notify_event().connect(sigc::mem_fun(*this, &ScrollHandler::mouseLeft));
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &ScrollHandler::scroll), 50);
}

ScrollHandler::~ScrollHandler(){}

bool ScrollHandler::mouseMotionEvent(GdkEventMotion* motion_event){
	this->last_mouse_position = Position(motion_event->x, motion_event->y);
	this->mouse_in_window = true;
	return true;
}

bool ScrollHandler::mouseEntered(GdkEventCrossing* crossing_event){
	this->mouse_in_window = true;
	return true;
}

bool ScrollHandler::mouseLeft(GdkEventCrossing* crossing_event){
	this->mouse_in_window = false;
	return true;
}

bool ScrollHandler::scroll(){
	int window_width = window.get_hadjustment()->get_page_size();
	int window_height = window.get_vadjustment()->get_page_size();

	if (!this->mouse_in_window){
		//El mouse esta fuera de la pantalla
		return true;
	}

	if (last_mouse_position.getX() < SPACE_TO_SCROLL){
		//Scroll a la izquierda
		this->window.get_hadjustment()->set_value(this->window.get_hadjustment()->get_value() - SCROLL_INCREMENT);
	}

	if (last_mouse_position.getX() > window_width - SPACE_TO_SCROLL){
		//Scroll a la derecha
		this->window.get_hadjustment()->set_value(this->window.get_hadjustment()->get_value() + SCROLL_INCREMENT);
	}

	if (last_mouse_position.getY() < SPACE_TO_SCROLL){
		//Scroll arriba
		this->window.get_vadjustment()->set_value(this->window.get_vadjustment()->get_value() - SCROLL_INCREMENT);
	}

	if (last_mouse_position.getY() > window_height - SPACE_TO_SCROLL){
		//Scroll abajo
		this->window.get_vadjustment()->set_value(this->window.get_vadjustment()->get_value() + SCROLL_INCREMENT);
	}

	return true;
}

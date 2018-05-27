#ifndef __VIEWTRANSFORMER_H__
#define __VIEWTRANSFORMER_H__

#include <gtkmm/layout.h>
#include "Position.h"

class ViewTransformer{
	private:
		Gtk::Layout& layout;

	public:
		ViewTransformer(Gtk::Layout& layout);
		~ViewTransformer();

		Position transformToScreen(const Position& position);
		Position transformToScreenAndMove(const Position& position, float width, float height);
		Position transformToPosition(const Position& position);
};

#endif

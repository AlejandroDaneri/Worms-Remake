#ifndef __VIEWTRANSFORMER_H__
#define __VIEWTRANSFORMER_H__

#include <gdkmm/screen.h>
#include "Position.h"

class ViewTransformer{
	private:
		Glib::RefPtr<Gdk::Screen> screen;

	public:
		ViewTransformer();
		~ViewTransformer();

		Position transformToScreen(const Position& position);
		Position transformToScreenAndMove(const Position& position, float width, float height);
		Position transformToPosition(const Position& position);
};

#endif

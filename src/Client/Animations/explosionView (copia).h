#ifndef __CLIENTEXPLOSIONVIEW_H__
#define __CLIENTEXPLOSIONVIEW_H__

#include <vector>
#include <gdkmm/pixbuf.h>
#include <gtkmm/image.h>
#include "Thread.h"

class BulletView;

class ExplosionView: public Thread{
	private:
		BulletView bulletView;
		std::vector<Glib::RefPtr<Gdk::Pixbuf>> animation_vector;
		Glib::RefPtr<Gdk::Pixbuf> animation;

	public:
		ExplosionView(BulletView&& bullet);
		~ExplosionView();

		void run();
};


#endif

#ifndef __CLIENTEXPLOSIONVIEW_H__
#define __CLIENTEXPLOSIONVIEW_H__

#include <vector>
#include <gdkmm/pixbuf.h>
#include "Thread.h"

class ViewsList;
class BulletView;

class ExplosionView: public Thread{
	private:
		BulletView& bulletView;
		ViewsList& viewList;
		int id;
		std::vector<Glib::RefPtr<Gdk::Pixbuf>> animation_vector;
		Glib::RefPtr<Gdk::Pixbuf> animation;

	public:
		ExplosionView(BulletView& bullet, ViewsList& viewList, int id);
		~ExplosionView();

		void run();
};


#endif

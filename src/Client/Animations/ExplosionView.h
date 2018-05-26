#ifndef __CLIENTEXPLOSIONVIEW_H__
#define __CLIENTEXPLOSIONVIEW_H__

#include <vector>
#include <gdkmm/pixbuf.h>
#include "Thread.h"
#include "BulletView.h"

class ExplosionView {
	private:
		BulletView bulletView;
		std::vector<Glib::RefPtr<Gdk::Pixbuf>> animation_vector;
		Glib::RefPtr<Gdk::Pixbuf> animation;
        std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator iter;

        bool startCallBack();

	public:
		ExplosionView(BulletView&& bullet);
		~ExplosionView();
        ExplosionView(ExplosionView&& other);

		void start();
		bool hasFinished();
};


#endif

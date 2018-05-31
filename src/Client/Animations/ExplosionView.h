#ifndef __CLIENTEXPLOSIONVIEW_H__
#define __CLIENTEXPLOSIONVIEW_H__

#include <vector>
#include <gdkmm/pixbuf.h>
#include "BulletView.h"

/* Clase que se encarga de reproducir la animacion de una explosion */
class ExplosionView {
	private:
		BulletView bulletView;
		std::vector<Glib::RefPtr<Gdk::Pixbuf>> animation_vector;
		Glib::RefPtr<Gdk::Pixbuf> animation;
		std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator iter;

		/* Callback de start */
		bool startCallBack();

	public:
		/* Constructor */
		ExplosionView(BulletView&& bullet);

		/* Destructor */
		~ExplosionView();

		/* Constructor por movimiento */
		ExplosionView(ExplosionView&& other);


		/* Realiza la animacion de la explosion */
		void start();

		/* Devuelve true si la animacion de la explosion finalizo */
		bool hasFinished();
};


#endif

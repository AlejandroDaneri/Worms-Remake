#ifndef WORMS_WALKINGANIMATION_H
#define WORMS_WALKINGANIMATION_H

#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <queue>

/* Clase que se encarga de actualizar la imagen del worm al
 * moverse obteniendo una animacion del worm caminando */
class WalkingAnimation {
	private:
		std::queue<Glib::RefPtr<Gdk::Pixbuf>> walk_queue;
		Glib::RefPtr<Gdk::Pixbuf> walk_image;
		Gtk::Image* worm_image;
		char dir;

	public:
		/* Constructor*/
		WalkingAnimation(Gtk::Image* worm_image);

		/* Destructor */
		~WalkingAnimation();

		/* Constructor por movimiento */
		WalkingAnimation(WalkingAnimation&& other);


		/* Actualiza la imagen del worm por la siguiente
		 * imagen del worm caminando */
		void setMovementImage(char new_dir);

		/* Setea la imagen del worm por la imagen actual del
		 * worm caminando */
		void setStaticImage(char new_dir);

		/* Devuelve la direccion del worm */
		char getDir() const;

		/* Actualiza el puntero de la imagen del worm */
		void updateWormImage(Gtk::Image* worm_image);
};


#endif //WORMS_WALKINGANIMATION_H

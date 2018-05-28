#ifndef __WORMLIFEVIEW_H__
#define __WORMLIFEVIEW_H__

#include <gtkmm/label.h>

/* Clase que se encarga de controlar el label de la vida
 * del worm */
class WormLifeView{
	private:
		Gtk::Label label;
		std::string color;

	public:
		/* Constructor */
		WormLifeView(int life, const std::string& color);

		/* Destructor */
		~WormLifeView();

		/* Constructor por movimiento */
		WormLifeView(WormLifeView&& other);

		/* Actualiza el label de vida del worm */
		void updateLife(int life);

		/* Devuelve el contenedor de la vida */
		Gtk::Widget& getWidget();
};


#endif

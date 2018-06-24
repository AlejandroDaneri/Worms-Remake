#ifndef WORMS_WEAPONANIMATION_H
#define WORMS_WEAPONANIMATION_H

#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <vector>
#include <string>

class WormView;

/* Clase que se encarga de controlar las animaciones
 * de las armas */
class WeaponAnimation {
private:
	std::vector<Glib::RefPtr<Gdk::Pixbuf>> scope_vector;
	Glib::RefPtr<Gdk::Pixbuf> scope_image;
	Gtk::Image* worm_image;
	int angle;
	sigc::connection my_connection;

	/* Actualiza las imagenes por las imagenes del arma nueva */
	void updateWeaponImage(const std::string& weapon);

	/* Callback */
	bool batHitCallBack(std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator& iter,
						const int width, char dir);

public:
	/* Constructor */
	WeaponAnimation(const std::string& weapon, Gtk::Image* worm_image);

	/* Destructor */
	~WeaponAnimation();

	/* Constructor por movimiento */
	WeaponAnimation(WeaponAnimation&& other);


	/* Cambia la imagen del worm con el arma actual por una imagen
	 * del worm con la nueva arma */
	void changeWeapon(const std::string& weapon, char dir);

	/* Setea la imagen del worm con el arma actual apuntando
	 * con el angulo especifico */
	void setWeaponImage(char dir);

	/* Realiza la animacion del disparo del arma */
	void weaponShootAnimation(const std::string& weapon, char dir);

	/* Actualiza el angulo, cambiando la imagen del arma
	 * por la correspondiente */
	void changeAngle(int angle, char dir);

	/* Actualiza el puntero de la imagen del worm */
	void updateWormImage(Gtk::Image* worm_image);

	void stopShootAnimation();
};


#endif //WORMS_WEAPONANIMATION_H

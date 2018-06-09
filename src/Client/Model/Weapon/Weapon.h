#ifndef __CLIENTWEAPON_H__
#define __CLIENTWEAPON_H__

#include <string>

/* Clase que se encarga de representar a las armas del juego */
class Weapon {
	protected:
		std::string name;
		unsigned int ammo;
		bool has_Scope;
		bool is_Timed;

	public:
		/* Constructor */
		Weapon(std::string name, int ammo);

		/* Destructor */
		~Weapon();

		/* Constructor por movimiento */
		Weapon(Weapon&& other);

		/* Operador = por movimiento */
		Weapon& operator=(Weapon&& other);


		/* Devuelve true si el arma tiene mira */
		virtual bool hasScope() const;

		/* Devuelve true si el arma es teledirigida */
		virtual bool isSelfDirected() const;

		/* Devuelve true si el arma es por tiempo */
		virtual bool isTimed() const;

		/* Devuelve true si el arma tiene potencia variable */
		virtual bool hasVariablePower() const;

		/* Devuelve el nombre del arma */
		virtual const std::string& getName() const;

		/* Disminuye la cantidad de municiones del arma */
		virtual void shoot();

		/* Devuelve true si el arma tiene balas */
		virtual bool hasAmmo() const;

		/* Devuelve la cantidad de balas */
		unsigned int getAmmo() const;
};
#endif

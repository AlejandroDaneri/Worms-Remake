#ifndef __POSITION_H__
#define __POSITION_H__

/* Clase que se encarga de representar posiciones en el plano */
class Position{
	private:
		float x;
		float y;

	public:
		/* Constructor */
		Position(float x, float y);

		/* Destructor */
		~Position();

		/* Devuelve true si las dos posiciones son iguales */
		bool operator==(const Position& other);

		/* Devuelve el valor en X de la posicion */
		float getX() const;

		/* Devuelve el valor en Y de la posicion */
        float getY() const;
};

#endif

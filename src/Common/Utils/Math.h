#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__

class Math{
	public:
	    /* Transforma grados geometricos a radianes */
		static float degreesToRadians(int angle);

		/* Transforma radianes a grados geometricos */
		static int radiansToDegrees(float angle);

		/* Devuelve el resultado del coseno para el angulo
		 * en grados geometricos */
		static float cosDegrees(int angle);

        /* Devuelve el resultado del seno para el angulo
         * en grados geometricos */
		static float sinDegrees(int angle);
};

#endif

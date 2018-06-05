#ifndef __GIRDERSIZE_H__
#define __GIRDERSIZE_H__

class GirderSize{
	private:
		//Normaliza el angulo entre 0 y 90
		static int normalizeAngle(int angle);
	public:
		//Devuelve el ancho de una viga en metros
		static float getGirderWidthMeters(int size, int angle);

		//Devuelve el ancho de una viga en pixeles
		static int getGirderWidthPixels(int size, int angle);

		//Devuelve el alto de una viga en metros
		static float getGirderHeightMeters(int size, int angle);

		//Devuelve el alto de una viga en pixeles
		static int getGirderHeightPixels(int size, int angle);
};

#endif


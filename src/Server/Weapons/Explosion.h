#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

class Explosion{
	private:
		int radius;
		int damage;

	public:
		Explosion(int radius, int damage);
		~Explosion();

		void attack();

};

#endif

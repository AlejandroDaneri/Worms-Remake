#ifndef __GAMEPARAMETERS_H__
#define __GAMEPARAMETERS_H__

#include <string>

class GameParameters{
	private:
		int bazooka_radius;
		int bazooka_damage;

	public:
		GameParameters(const std::string& config_file);
		~GameParameters();

		int get_bazooka_radius();
		int get_bazooka_damage();

};

#endif

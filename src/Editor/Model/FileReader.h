
#ifndef WORMS_FILEREADER_H
#define WORMS_FILEREADER_H

#include <fstream>
#include "MapObject.h"
#include <yaml.h>
#include <WeaponNames.h>
#include <ConfigFields.h>
#include <string>
#include <vector>
#include <gtkmm/image.h>

// Clase que se encarga de manejar la carga de un mapa
class FileReader{
private:
    std::fstream file;
	std::string filename;

public:
	explicit FileReader(const std::string &filename);

	// Carga todos los componentes de un mapa desde un archivo YAML
    void read(std::vector<std::vector<double>> &worms,
              std::vector<std::vector<double>> &girders,
              std::vector<int> &weps_ammo,
              unsigned int &worm_life, Glib::RefPtr<Gdk::Pixbuf> &background);
};


#endif //WORMS_FILEREADER_H

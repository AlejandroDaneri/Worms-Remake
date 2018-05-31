
#ifndef WORMS_FILEREADER_H
#define WORMS_FILEREADER_H

#include <fstream>
#include "MapObject.h"
#include <yaml.h>
#include <WeaponNames.h>
#include <ConfigFields.h>

class FileReader{
private:
	std::fstream file;
public:

    explicit FileReader(const std::string &filename);


    void read(std::vector<std::vector<double>> &worms,
              std::vector<std::vector<double>> &girders,
              std::vector<int> &weps_ammo,
              unsigned int &worm_life);
};


#endif //WORMS_FILEREADER_H

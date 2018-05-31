
#ifndef WORMS_FILEWRITER_H
#define WORMS_FILEWRITER_H

#include <fstream>
#include "MapObject.h"
#include <yaml.h>
#include <WeaponNames.h>
#include <ConfigFields.h>

class FileWriter{
private:
	std::fstream file;
public:
    explicit FileWriter(const std::string &filename);

    void
    save(std::vector<int> weapons,
         const std::vector<std::vector<double>> &worms,
         const std::vector<std::vector<double>> &girders,
         const unsigned int &worm_life);
};


#endif //WORMS_FILEWRITER_H

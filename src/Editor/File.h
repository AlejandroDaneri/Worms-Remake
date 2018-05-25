
#ifndef WORMS_FILE_H
#define WORMS_FILE_H


#include <fstream>
#include "MapObject.h"
#include <yaml.h>
#include <WeaponNames.h>
#include <ConfigFields.h>

class File {
protected:
    std::fstream file;
public:

    File(const std::string &filename, const std::ios_base::openmode &openmode);

    virtual ~File();
};


#endif //WORMS_FILE_H


#include <yaml.h>
#include "File.h"

File::File(const std::string &filename, const std::ios_base::openmode &openmode)
        : file(std::move(std::fstream(filename, openmode))) {
}

File::~File() {
    file.close();
}

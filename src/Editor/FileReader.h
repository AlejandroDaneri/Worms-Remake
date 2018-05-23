
#ifndef WORMS_FILEREADER_H
#define WORMS_FILEREADER_H


#include "File.h"

class FileReader : public File {
public:

    explicit FileReader(const std::string &filename);

    void read();
};


#endif //WORMS_FILEREADER_H

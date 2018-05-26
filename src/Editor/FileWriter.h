
#ifndef WORMS_FILEWRITER_H
#define WORMS_FILEWRITER_H


#include "File.h"

class FileWriter : public File {
public:
    explicit FileWriter(const std::string &filename);

    void
    save(std::vector<int> weapons,
         const std::vector<std::vector<double>> &worms,
         const std::vector<std::vector<double>> &girders,
         unsigned int worm_life);
};


#endif //WORMS_FILEWRITER_H

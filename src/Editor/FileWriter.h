
#ifndef WORMS_FILEWRITER_H
#define WORMS_FILEWRITER_H


#include "File.h"

class FileWriter : public File {
public:
    explicit FileWriter(const std::string &filename);

    void
    save(const std::vector<int> &weapons,
         std::vector<std::vector<double>> &worms,
         std::vector<std::vector<double>> &girders);
};


#endif //WORMS_FILEWRITER_H

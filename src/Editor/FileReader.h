
#ifndef WORMS_FILEREADER_H
#define WORMS_FILEREADER_H


#include "File.h"

class FileReader : public File {
public:

    explicit FileReader(const std::string &filename);


    void read(std::vector<std::vector<double>>& worms,
                  std::vector<std::vector<double>>& girders,
                  std::vector<std::vector<int>>& weps_ammo);

    void read(std::vector<std::vector<double>> &worms,
              std::vector<std::vector<double>> &girders,
              std::vector<int> &weps_ammo);
};


#endif //WORMS_FILEREADER_H

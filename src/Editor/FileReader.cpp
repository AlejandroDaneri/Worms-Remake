
#include "FileReader.h"

FileReader::FileReader(const std::string &filename) : File(filename,
                                                           std::fstream::in) {}

void FileReader::read() {
    /*/
      clean();
      YAML::Node config = YAML::LoadFile("config_editor.yaml");
  /*//*/
    int worms_life = config["worms_life"].as<int>();
    std::cout << "worms_life: " << worms_life << std::endl;

    //convierto directamente a map
    std::map<std::string, int> ammo = config["weapon_ammo"].as<std::map<std::string, int>>();

    std::cout << "En el map: ammo bazooka: " << ammo["Bazooka"] << std::endl;
    std::cout << "ammo dynamite: " << ammo["Dynamite"]<< std::endl;

/*//*/
    //carga de  worms
    std::vector<std::vector<float>> worms = config["worms"].as<std::vector<std::vector<float>>>();

    //std::cout <<"\nworms:\n\n";
    for (auto &worm : worms) {
        MapObject new_worm(Gtk::Image(pallete.front()), Pos(worm[0], worm[1]));
        Gtk::Image *new_image = new_worm.getImageWidget();
        put(*new_image, new_worm.getPrintableWidth(),
            new_worm.getPrintableHeight());
        new_image->show();
        objects.emplace_back(std::make_pair(1, std::move(new_worm)));
        //std::cout << "pos_x: " << worm[0] << " pos_y: " << worm[1] << std::endl;

    }

    //carga de vigas
    std::vector<std::vector<float>> girders = config["girders"].as<std::vector<std::vector<float>>>();

    //std::cout <<"\nGirders:\n\n";
    for (auto &girder : girders) {
        MapObject new_girder(Gtk::Image(pallete[1]),
                             Pos(girder[1], girder[2], girder[3]));
        objects.emplace_back(std::make_pair(2, std::move(new_girder)));
        //std::cout << "len: " << girder[0] <<"  pos_x: " << girder[1] << " pos_y: " << girder[2] << "  rotation: "<< girder[3] << std::endl;
    }
    /*/
}

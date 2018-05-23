
#include <yaml.h>
#include "Map.h"

//TODO: cambiar posicion por centro
void Map::undo() {
    if (!objects.empty())
        this->objects.pop_back();
}

void Map::clean() {
    this->objects.clear();
}

void Map::add(unsigned int &id, double &x, double &y) {
    MapObject new_object(x, y);
    objects.emplace_back(std::make_pair(id, new_object));
}

void Map::moveLast(double &x, double &y) {
    MapObject &object = objects.back().second;
    object.updatePosition(x, y);
}

int Map::turnLast() {
    MapObject &object = objects.back().second;
    return object.turn();
}

bool Map::lastIsGirder() {
    return objects.back().first == 2;
}

void Map::getObjects(std::vector<std::vector<double>> &worms,std::vector<std::vector<double>> &girders) const{
    //gusanos
    for (auto &object : objects) {
        double x,y;
        object.second.getPosition(x,y);
        if (object.first == 1) {//worm
            std::vector<double> position;
            position.push_back(x); //pos x
            position.push_back(y); //pos_y
            worms.push_back(position);
        } else if (object.first == 2) { //viga corta
            std::vector<double> data;
            data.push_back(3); //len
            data.push_back(x); //pos_x
            data.push_back(y); //pos_y
            data.push_back(object.second.getAngle()); //rotation
            girders.push_back(data);
        }
    }

}

void Map::load_signal() {
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


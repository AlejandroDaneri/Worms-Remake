
#include <gtkmm/builder.h>
#include <gtkmm/scrolledwindow.h>
#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"
#include "editor_Map.h"
#include "editor_Pos.h"

Map::Map(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Layout(cobject),
          m_builder(builder),
          button_id(1),
          action(0)
{
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this,&Map::on_button_clicked));
    pallete.emplace_back("resources/images/right_worm.png");
    for (int i = 0; i < 180; i=i+10) {
        pallete.emplace_back("resources/images/Girder/girder_3_"+std::to_string(i)+".png");
    }
}


bool Map::on_button_clicked(GdkEventButton *button_event) {
    if(action==0) { //nuevo
        Gtk::Image new_image(pallete[button_id-1]);
        Pos pos(button_event->x,button_event->y);

        const Glib::RefPtr<Gdk::Pixbuf> &img = new_image.get_pixbuf();

        put(new_image, pos.getPrintableWidth(img->get_width()),
            pos.getPrintableHeigth(img->get_height()));
        new_image.show();
        MapObject object(std::move(new_image),pos);
        objects.emplace_back(std::make_pair(button_id,std::move(object)));


    } else if(action==1){ //mover

        MapObject &object = objects.back().second;
        const Glib::RefPtr<Gdk::Pixbuf> &img = object.getImagePixbuf();
        Gtk::Image* image = object.getImageWidget();
        object.updatePos(button_event->x, button_event->y);

        move(*image, object.getPrintableWidth(img->get_width()),
             object.getPrintableHeight(img->get_height()));

        action=0;
    }
    return true;
}

void Map::undo(){
    objects.pop_back();
}

void Map::clean(){
    objects.clear();
}

void Map::clicked_signal(unsigned int id) {
    button_id=id;
}

void Map::move_signal() {
    action=1;
}

void Map::turn_signal() {
    MapObject &object = objects.back().second;

    Gtk::Image new_image(pallete[(object.turn()%180)/10+1]);
    const Glib::RefPtr<Gdk::Pixbuf> &pixb = object.getImagePixbuf();
    const Pos &pos = object.getPos();

    objects.pop_back();
    put(new_image, object.getPrintableWidth(pixb->get_width()),
        object.getPrintableHeight(pixb->get_height()));
    new_image.show();
    MapObject new_obj(std::move(new_image),std::move(pos));
    objects.emplace_back(std::make_pair(button_id,std::move(new_obj)));
}

void Map::save_signal() {
    //gusanos
    std::vector<std::vector<double>> worms;
    std::vector<std::vector<double>> girders;
    for (auto &object : objects) {
        const Pos &pos = object.second.getPos();
        if(object.first==1){//worm
            std::vector<double> position;
            position.push_back(pos.getX()); //pos x
            position.push_back(pos.getY()); //pos_y
            worms.push_back(position);
        } else if(object.first==2){ //viga corta
            std::vector<double> data;
            data.push_back(3); //len
            data.push_back(pos.getX()); //pos_x
            data.push_back(pos.getY()); //pos_y
            data.push_back(pos.getAngle()); //rotation
            girders.push_back(data);
        }
    }

    YAML::Emitter out;

    out << YAML::BeginMap;

    out << YAML::Key << "worms_life";
    out << YAML::Value << 200;

    //armas
    out << YAML::Key << "weapon_ammo";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "Bazooka";
    out << YAML::Value << 99999;
    out << YAML::Key << "Mortar";
    out << YAML::Value << 10;
    out << YAML::Key << "GreenGrenade";
    out << YAML::Value << 99999;
    out << YAML::Key << "RedGrenade";
    out << YAML::Value << 10;
    out << YAML::Key << "Banana";
    out << YAML::Value << 5;
    out << YAML::Key << "HolyGrenade";
    out << YAML::Value << 2;
    out << YAML::Key << "Dynamite";
    out << YAML::Value << 5;
    out << YAML::Key << "Bat";
    out << YAML::Value << 99999;
    out << YAML::Key << "AirAttack";
    out << YAML::Value << 2;
    out << YAML::Key << "Teleportation";
    out << YAML::Value << 99999;

    out << YAML::EndMap;

    //posicion de gusanos
    out << YAML::Key << "worms";
    out << worms;

    out << YAML::Key << "girders";
    out << girders;

    /*out << YAML::Value << YAML::BeginSeq;

    out << YAML::Value << YAML::BeginSeq << 50 << 100 << YAML::EndSeq;
    out << YAML::Value << YAML::BeginSeq << 60 << 100 << YAML::EndSeq;
    out << YAML::Value << YAML::BeginSeq << 70 << 100 << YAML::EndSeq;

    out << YAML::EndSeq;*/


    out << YAML::EndMap;

    std::cout << "Here's the output YAML:\n\n\n" << out.c_str()<<std::endl;

    //lo guardo en un archivo
    std::ofstream file("config_editor.yaml");
    file << out.c_str();

}

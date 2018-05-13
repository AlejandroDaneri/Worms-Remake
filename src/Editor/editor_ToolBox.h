#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H


#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/togglebutton.h>

#define WORM_BUTTON_ID 1
#define GIRDER_BUTTON_ID 2


class ToolBox : public Gtk::Grid{
private:
    unsigned short item_pressed;

    //Child widgets
    Gtk::Button turn;
    Gtk::ToggleButton worm, girder;// deberia ser toggle

public:
    ToolBox();


    void on_button_clicked(int id);

    std::string getActualItemImagePath();
};


#endif //WORMS_TOOLBOX_H

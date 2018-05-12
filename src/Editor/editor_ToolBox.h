#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H


#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/togglebutton.h>


class ToolBox : public Gtk::Grid{
private:
    //Child widgets
    Gtk::Button turn;
    Gtk::ToggleButton worm, girder;

public:
    ToolBox();

    void on_button_clicked();

};


#endif //WORMS_TOOLBOX_H

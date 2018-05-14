#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H


#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/window.h>
#include <gtkmm/notebook.h>
#include <gtkmm/hvbox.h>

#define WORM_BUTTON_ID 1
#define GIRDER_BUTTON_ID 2


class ToolBox : public Gtk::Grid{
private:
    unsigned short item_pressed;

    //Child widgets
    Gtk::Button turn,armory;
    Gtk::ToggleButton worm, girder;// deberia ser toggle
    bool change_win;


public:
    ToolBox();

    void on_button_clicked(int id);

    std::string getActualItemImagePath();

protected:
    bool on_button_release_event(GdkEventButton *release_event) override;

};


#endif //WORMS_TOOLBOX_H

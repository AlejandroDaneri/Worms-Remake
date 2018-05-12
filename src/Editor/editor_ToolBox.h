#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H


#include <gtkmm/hvbox.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>


class editor_ToolBox : public Gtk::HBox{
private:
    //Child widgets
    Gtk::Button worm, girder;


public:
    editor_ToolBox();

    void on_button_clicked();
};


#endif //WORMS_TOOLBOX_H

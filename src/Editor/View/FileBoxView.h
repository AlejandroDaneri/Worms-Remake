
#ifndef WORMS_FILEBOXVIEW_H
#define WORMS_FILEBOXVIEW_H

#include <gtkmm/builder.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include "Controllers/FileBoxController.h"

class FileBoxController;

class FileBoxView : public Gtk::Grid {
private:
    Gtk::Button *save;
    Gtk::Button *load;
    Gtk::Button *new_map;
    std::shared_ptr<FileBoxController> file_box_controller;
public:
    FileBoxView(BaseObjectType *cobject,
                const Glib::RefPtr<Gtk::Builder> &builder);

    void linkControler(std::shared_ptr<FileBoxController> controller);
};


#endif //WORMS_FILEBOXVIEW_H

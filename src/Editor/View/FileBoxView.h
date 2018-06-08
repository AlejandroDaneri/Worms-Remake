
#ifndef WORMS_FILEBOXVIEW_H
#define WORMS_FILEBOXVIEW_H

#include <gtkmm/builder.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include "FileBoxController.h"

class FileBoxController;

// Clase que se encarga de manipular la zona de archivos
class FileBoxView : public Gtk::Grid {
private:
    Gtk::Button *save;
    Gtk::Button *load;
    Gtk::Button *new_map;
    std::shared_ptr<FileBoxController> file_box_controller;
public:
    FileBoxView(BaseObjectType *cobject,
                const Glib::RefPtr<Gtk::Builder> &builder);

    // Enlaza el controlador a la vista
    void bindController(std::shared_ptr<FileBoxController> controller);
};


#endif //WORMS_FILEBOXVIEW_H

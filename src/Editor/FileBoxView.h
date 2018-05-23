
#ifndef WORMS_FILEBOXVIEW_H
#define WORMS_FILEBOXVIEW_H


#include <gtkmm/builder.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include "FileBoxController.h"

class FileBoxController;

class FileBoxView : public Gtk::Grid{
private:
    const Glib::RefPtr<Gtk::Builder> & m_builder;
    Gtk::Button *save;
    Gtk::Button *load;
    std::shared_ptr<FileBoxController> file_box_controller;
public:
    FileBoxView(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    void linkControler(std::shared_ptr<FileBoxController> controller);
};


#endif //WORMS_FILEBOXVIEW_H


#ifndef WORMS_FILECONTROLLER_H
#define WORMS_FILECONTROLLER_H

#include <gtkmm/filechooserdialog.h>
#include "FileBoxView.h"
#include "UsablesController.h"
#include "MapController.h"

class FileBoxController {
private:
    UsablesController &weapons_controller;
    std::shared_ptr<MapController> map_controller;
    Gtk::FileChooserDialog* save_dialog;
    Gtk::FileChooserDialog* open_dialog;
    Gtk::Label* map_name;

public:
    FileBoxController(UsablesController &wep_controller,
                      std::shared_ptr<MapController> map_controller,
                      const Glib::RefPtr<Gtk::Builder> &builder);

    void onSaveClicked() const;

    void onLoadClicked() const;

    void onNewClicked() const;
};


#endif //WORMS_FILECONTROLLER_H

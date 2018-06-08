
#ifndef WORMS_FILECONTROLLER_H
#define WORMS_FILECONTROLLER_H

#include <gtkmm/filechooserdialog.h>
#include "FileBoxView.h"
#include "UsablesController.h"
#include "MapController.h"

// Clase que se encarga de establecer una conexion entre la seccion de archivos
// y  el resto del programa
class FileBoxController {
private:
    UsablesController &usables_controller;
    std::shared_ptr<MapController> map_controller;
    Gtk::FileChooserDialog* save_dialog;
    Gtk::FileChooserDialog* open_dialog;
    Gtk::Label* map_name;

public:
    FileBoxController(UsablesController &wep_controller,
                      std::shared_ptr<MapController> map_controller,
                      const Glib::RefPtr<Gtk::Builder> &builder);

    // Se encarga de mostrar un cuadro de dialogo para seleccionar un archivo
    // cuando se eligio guardar en la vista
    void onSaveClicked() const;

    // Se encarga de mostrar un cuadro de dialogo para seleccionar un archivo
    // cuando se eligio cargar en la vista
    void onLoadClicked() const;

    // Crea un nuevo mapa y actualiza la informacion del nombre del mapa actual
    void onNewClicked() const;
};


#endif //WORMS_FILECONTROLLER_H


#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/layout.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/hvbox.h>
#include "MapView.h"
#include "MapController.h"

#define WORM_BUTTON_ID 1
#define GIRDER_3_BUTTON_ID 3
#define GIRDER_6_BUTTON_ID 6
class MapController;

// Clase que contiene la vista de la botonera
class ToolBoxView : public Gtk::Grid {
private:
    Gtk::Button *erase;
    MapController *map_controller;
    Gtk::ToggleButton *worm;
    Gtk::ToggleButton *girder_3m;
    Gtk::ToggleButton *girder_6m;
    Gtk::Button *move;

    Gtk::Button *turnccw;
    Gtk::Button *turncw;
    Gtk::Button *change_bg;
    Gtk::ToggleButton *mode;
    Gtk::Image* selected;
    bool processing;

    // Deja en un estado consistente la zona "Agregar"
    void leaveConsistent();

public:
    ToolBoxView(BaseObjectType *cobject,
                const Glib::RefPtr<Gtk::Builder> &builder);

    // Se ejecuta cuando se selecciona un elemento de la zona "Agregar"
    void onNewObjectClicked(unsigned int id);

    // Habilita para el usuario la interacción con las acciones de la zona
    // "Seleccion"
    void enableMovingItems();

    // Deshabilita para el usuario la interacción con las acciones de la zona
    // "Seleccion"
    void disableMovingItems();

    // Enlaza la vista con el controlador
    void bindController(MapController *controller);

    // Alterna la vista entre el modo "Agregar" y modo "Seleccion"
    void changeMode();

    // Muestra el objeto seleccionado en el recuadro en la zona "Seleccion"
    void showSelected(int id);

    // Vacía el recuadro en la zona "Seleccion"
    void hideSelected();

    // Sale del modo "Seleccion"
    void closeSelectionMode();

    void hideRotatingButtons();
};


#endif //WORMS_TOOLBOX_H

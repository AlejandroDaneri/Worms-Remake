
#ifndef WORMS_MAPCONTROLLER_H
#define WORMS_MAPCONTROLLER_H

#include <gtkmm/filechooserdialog.h>
#include <string>
#include <vector>
#include "MapView.h"
#include "Map.h"
#include "ToolBoxView.h"

class MapView;
class ToolBoxView;

// Clase que se encarga de comunicar la vista con el modelo, y a su vez, se
// comunica con el resto del programa
class MapController {
    Map model;
    MapView *view;
    ToolBoxView *toolBox;
    unsigned int item_id_to_add;
    unsigned int actual_mode;
    int index_object_selected;
    Gtk::FileChooserDialog* background_dialog;

    void turn(const int &rotation);
    
public:
	/* Constructor */
    MapController(Map model, const Glib::RefPtr<Gtk::Builder> &builder);

    /* Cambia al modo de agregado, en donde el objeto
     * a agregar es el de id */
    void addModeSignal(const unsigned int &id);

    /* Envia una señal de borrado */
    void eraseSignal();

    /* Envia una señal de nuevo mapa */
    void newMapSignal();

	/* Envia una señal de movimiento */
    void moveSignal();

	/* Envia una señal de rotacion anti horario */
    void turnCCWSignal();

	/* Envia una señal de click sobre el mapa */
    void mapClickedSignal(GdkEventButton *event_button);

	/* Obtiene los objetos del mapa */
    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;

	/* Carga los worms y las vigas en el mapa */
    void loadObjects(std::vector<std::vector<double>> &worms,
                     std::vector<std::vector<double>> &girders);

	/* Envia una señal de rotacion horaria */
    void turnCWSignal();

	/* Envia una señal de cambio de imagen de fondo */
    void changeBackgroundSignal() const;

	/* Envia una señal de cambio de modo */
    void changeModeSignal();

	/* Devuelve la imagen de fondo */
    Glib::RefPtr<const Gdk::Pixbuf> getBackground() const;

	/* Carga la imagen de fondo */
    void loadBackground(Glib::RefPtr<Gdk::Pixbuf> &background);
};


#endif //WORMS_MAPCONTROLLER_H

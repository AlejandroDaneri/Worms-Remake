
#ifndef WORMS_MAP_H
#define WORMS_MAP_H

#include <gtkmm/builder.h>
#include <gtkmm/layout.h>
#include <gtkmm/image.h>
#include <string>
#include <vector>
#include "MapController.h"
#include "Water.h"
#include "ScrollHandler.h"

class MapController;

// Clase que se encarga de manipular la vista del mapa
class MapView : public Gtk::Layout {
private:
    std::vector<Gtk::Image> contained_objects;
    std::vector<std::vector<std::string>> objects_pallete;
    MapController *controller;
    std::vector<Gtk::Image> background;
    Water water;
    ScrollHandler scroll_handler;


    // Inicializa el vector de imagenes de los worms
    void initializeWormsImages();

    // Inicializa el vector de imagenes de las vigas
    void initializeGirderImages();

    // Establece la posicion actual del mapa a mostrar
    void setInitialPosition();

    // Dibuja nuevamente el contenido del mapa
    void redrawMap();

public:
    MapView(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    // Se ejecuta al clickear el mapa
    bool onButtonClicked(GdkEventButton *button_event);

    // Borra el objeto en la posición indicada
    void erase(const int &index);

    // Elimina todo el contenido del mapa
    void clean();

    // Enlaza el controlador a la vista
    void bindController(MapController *map_controller);

    // Agregar un nuevo objeto al mapa, en la posicion (x,y)
    void add(const unsigned int &id, const double &x, const double &y,
             const int &angle = 0);

    // Gira el objeto seleccionado
    bool turn(const unsigned int &id, const int &angle, const int &index);

    // Cambia el fondo actual
    void changeBackground(const std::string &path);

    // Selecciona el objeto en la posición (x,y)
    int select(const double &x, const double &y);

    // Mueve el objeto seleccionado a la posicón (x.y)
    void move(const int& index, const double &x, const double &y);

    // Obtiene el nombre del fondo actual
    Glib::RefPtr<const Gdk::Pixbuf> getBackground() const;

    // Establece el fondo especificado por su nombre
    void loadBackground(const std::string &name);
};

#endif //WORMS_MAP_H

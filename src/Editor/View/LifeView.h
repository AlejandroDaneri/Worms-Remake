
#ifndef WORMS_LIFEVIEW_H
#define WORMS_LIFEVIEW_H


#include <gtkmm/spinbutton.h>
#include <gtkmm/builder.h>

// Clase que se encarga de manipular la vista de la vida
class LifeView : public Gtk::SpinButton {
private:
    const unsigned int default_hp;
public:
    LifeView(BaseObjectType *cobject,
             const Glib::RefPtr<Gtk::Builder> &builder);

    // Establece el valor por defecto de la vida
    void reset();

    // Establece un nuevo valor a mostrar en la vista de la vida
    void update(const unsigned int &new_life);
};


#endif //WORMS_LIFEVIEW_H


#ifndef WORMS_MAP_H
#define WORMS_MAP_H

#include <gtkmm/layout.h>
#include <gtkmm/image.h>

class Map : public Gtk::Layout {
private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    std::vector<Gtk::Image> objects;

public:
    Map(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);
    bool on_button_clicked(GdkEventButton *button_event);

    void undo();

    void clean();
};


#endif //WORMS_MAP_H

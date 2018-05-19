
#ifndef WORMS_MAP_H
#define WORMS_MAP_H

#include <gtkmm/layout.h>
#include <gtkmm/image.h>
#include "editor_Pos.h"

class Map : public Gtk::Layout {
private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    std::vector<std::pair<Gtk::Image,Pos>> objects;
    unsigned int button_id,action;
    std::map<unsigned int,std::string> pallete;

public:
    Map(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);
    bool on_button_clicked(GdkEventButton *button_event);

    void undo();

    void clean();

    void clicked_signal(unsigned int id);

    void move_signal();
};


#endif //WORMS_MAP_H

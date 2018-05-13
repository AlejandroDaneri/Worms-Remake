#ifndef WORMS_MAPAREA_H
#define WORMS_MAPAREA_H


#include <gtkmm/drawingarea.h>
#include <gtkmm/image.h>
#include "editor_ToolBox.h"

class MapArea : public Gtk::DrawingArea{
private:
    int x,y;
    Glib::RefPtr<Gdk::Pixbuf> new_image;
    bool ok;
    ToolBox *toolBox;

    bool on_button_press_event(GdkEventButton *button_event) override;

    bool on_draw(const ::Cairo::RefPtr<::Cairo::Context> &cr) override;


public:
    MapArea();

    MapArea(ToolBox *toolBox);


};


#endif //WORMS_MAPAREA_H

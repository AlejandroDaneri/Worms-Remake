
#include "Editor.h"

typedef const Glib::RefPtr<Gtk::Builder> Builder;

Editor::Editor(BaseObjectType *cobject, Builder &builder):
        Gtk::Window(cobject),
        usables_controller(builder) {
    maximize();
    builder->get_widget("map_window", map_window);

    std::shared_ptr<MapController> map_controller
            (new MapController(map_model, builder));

    builder->get_widget_derived("filebox", filebox);
    std::shared_ptr<FileBoxController> filebox_controller(
            new FileBoxController(usables_controller, map_controller,builder));
    filebox->bindController(filebox_controller);

    show_all_children();
}

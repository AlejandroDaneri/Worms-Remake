
#include "Editor.h"

Editor::Editor(BaseObjectType *cobject,
               const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Window(cobject),
          weps_list_controller(builder) {
    maximize();
    builder->get_widget("map_window", map_window);
    map_window->override_background_color(Gdk::RGBA("lightgreen"));

    builder->get_widget_derived("map", map);
    builder->get_widget_derived("toolbox", toolbox);
    std::shared_ptr<MapController> map_controller
            (new MapController(map_model, *map));
    toolbox->linkController(map_controller);

    builder->get_widget_derived("filebox", filebox);
    std::shared_ptr<FileBoxController> filebox_controller(
            new FileBoxController(weps_list_controller, map_controller));
    filebox->linkControler(filebox_controller);

    show_all_children();
}

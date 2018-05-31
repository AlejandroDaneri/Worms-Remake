
#include "Editor.h"

Editor::Editor(BaseObjectType *cobject,
               const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Window(cobject),
          weps_list_controller(builder) {

    maximize();
    builder->get_widget("map_window", map_window);

    std::shared_ptr<MapController> map_controller
            (new MapController(map_model, builder));

    builder->get_widget_derived("filebox", filebox);
    std::shared_ptr<FileBoxController> filebox_controller(
            new FileBoxController(weps_list_controller, map_controller,builder));
    filebox->linkControler(filebox_controller);

    show_all_children();
}

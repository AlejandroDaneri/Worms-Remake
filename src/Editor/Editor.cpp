
#include "Editor.h"

Editor::Editor(BaseObjectType *cobject,
               const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Window(cobject),
          m_builder(builder),

        //weapons
          weplist(m_builder),
          weps_list_controller(weplist, weps_reset_button) {
    maximize();
    m_builder->get_widget("map_window", map_window);


    m_builder->get_widget_derived("map", map);
    m_builder->get_widget_derived("toolbox", toolbox);

    MapController *map_controller = new MapController(map_model, *map);
    toolbox->linkController(map_controller);
    map->linkController(map_controller);

    m_builder->get_widget("btn_reset_wep", weps_reset_button);
    weps_reset_button->signal_clicked().connect(
            sigc::mem_fun(weps_list_controller,
                          &WeaponsListController::on_reset_clicked));

    map_window->override_background_color(Gdk::RGBA("lightgreen"));
    show_all_children();
}

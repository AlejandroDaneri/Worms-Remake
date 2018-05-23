
#include "Editor.h"

Editor::Editor(BaseObjectType *cobject,
               const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Window(cobject),
          m_builder(builder),
          weps_list_controller(m_builder, weps_reset_button)
{
    maximize();
    m_builder->get_widget("map_window", map_window);
    map_window->override_background_color(Gdk::RGBA("lightgreen"));

    m_builder->get_widget_derived("map", map);
    m_builder->get_widget_derived("toolbox", toolbox);
    std::shared_ptr<MapController> map_controller (new MapController(map_model, *map));
    toolbox->linkController(map_controller);

    m_builder->get_widget("btn_reset_wep", weps_reset_button);
    weps_reset_button->signal_clicked().connect(
            sigc::mem_fun(weps_list_controller,
                          &WeaponsListController::on_reset_clicked));


    show_all_children();
}

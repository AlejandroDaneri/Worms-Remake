
#include <Path.h>
#include <string>
#include <vector>
#include <gtkmm/image.h>
#include "FileBoxController.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "InvalidMapError.h"

static const char *const NEW_FILE_NAME = "Sin titulo.yaml";

FileBoxController::FileBoxController(UsablesController &wep_controller,
        std::shared_ptr<MapController> map_controller,
        const Glib::RefPtr<Gtk::Builder> &builder )
        : usables_controller(wep_controller),
          map_controller(std::move(map_controller))
{
    builder->get_widget("save_dialog",save_dialog);
    save_dialog->add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    save_dialog->add_button("Guardar", Gtk::RESPONSE_OK);

    builder->get_widget("map_name",map_name);

    builder->get_widget("open_dialog",open_dialog);
    open_dialog->add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    open_dialog->add_button("Abrir", Gtk::RESPONSE_OK);
}

void FileBoxController::onSaveClicked() const {
    try {
        std::vector<std::vector<double>> worms;
        std::vector<std::vector<double>> girders;
        map_controller->getObjects(worms, girders);
        auto background = map_controller->getBackground();

        std::vector<int> weapons_ammo;
        unsigned int life;
        usables_controller.getWeaponsAndLife(weapons_ammo, life);

        save_dialog->set_current_folder(MAPS_PATH);
        save_dialog->set_current_name(map_name->get_text());
        int result = save_dialog->run();
        if (result==Gtk::RESPONSE_OK){
            std::string path = save_dialog->get_filename();
            std::string filename = save_dialog->get_current_name();
            map_name->set_label(filename);

            FileWriter file(path);
            file.save(weapons_ammo, worms, girders, life, background);
        }
        save_dialog->hide();
    } catch(const InvalidMapError &error){
        error.what();
    }
}

void FileBoxController::onLoadClicked() const {
    open_dialog->set_current_folder(MAPS_PATH);
    int result = open_dialog->run();
    if (result==Gtk::RESPONSE_OK) {
        std::string filename = open_dialog->get_filename();
        map_name->set_label(open_dialog->get_current_name());

        std::vector<std::vector<double>> worms;
        std::vector<std::vector<double>> girders;
        std::vector<int> weps_ammo;
        unsigned int life;
        Glib::RefPtr<Gdk::Pixbuf> background;

        FileReader file(filename);
        file.read(worms, girders,
                  weps_ammo, life, background);

        map_controller->loadBackground(background);
        usables_controller.loadWeapons(weps_ammo, life);
        map_controller->loadObjects(worms, girders);
    }
    open_dialog->hide();
}


void FileBoxController::onNewClicked() const {
    map_name->set_label(NEW_FILE_NAME);
    usables_controller.onResetSignal();
    map_controller->newMapSignal();
}


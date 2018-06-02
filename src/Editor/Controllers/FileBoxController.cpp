
#include <Path.h>
#include "FileBoxController.h"
#include "Modelo/FileWriter.h"
#include "Modelo/FileReader.h"
#include "Modelo/InvalidMapError.h"

FileBoxController::FileBoxController(WeaponsAndLifeController &wep_controller,
        std::shared_ptr<MapController> map_controller,
        const Glib::RefPtr<Gtk::Builder> &builder )
        : weapons_controller(wep_controller),
          map_controller(std::move(map_controller))
{
    builder->get_widget("save_dialog",save_dialog);
    builder->get_widget("map_name",map_name);

    save_dialog->add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    save_dialog->add_button("Guardar", Gtk::RESPONSE_OK);

    builder->get_widget("open_dialog",open_dialog);

    open_dialog->add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    open_dialog->add_button("Abrir", Gtk::RESPONSE_OK);

}

void FileBoxController::onSaveClicked() const {
    try {
        std::vector<std::vector<double>> worms;
        std::vector<std::vector<double>> girders;


        map_controller->getObjects(worms, girders);
        std::string background= map_controller->getBackgroundName();

        std::vector<int> weapons_ammo;
        unsigned int life;
        weapons_controller.getWeapons(weapons_ammo, life);

        save_dialog->set_current_folder(MAPS_PATH);
        save_dialog->set_current_name(NEW_FILE_NAME);
        int result = save_dialog->run();
        if (result==Gtk::RESPONSE_OK){
            std::string filename = save_dialog->get_filename(); //revisar extension archivo
            map_name->set_label(save_dialog->get_current_name());
            FileWriter file(filename);
            file.save(weapons_ammo, worms,
                      girders, life,background);
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

        std::string background;

        FileReader file(filename);
        std::vector<std::vector<double>> worms;
        std::vector<std::vector<double>> girders;
        std::vector<int> weps_ammo;
        unsigned int life;
        file.read(worms, girders,
                  weps_ammo, life, background);
        map_controller->loadBackground(background);
        weapons_controller.loadWeapons(weps_ammo, life);
        map_controller->loadObjects(worms, girders);
    }
    open_dialog->hide();
}


void FileBoxController::onNewClicked() const {
    map_name->set_label(NEW_FILE_NAME);
    weapons_controller.on_reset_clicked();
    map_controller->clean();
}


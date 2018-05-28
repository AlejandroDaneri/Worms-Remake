
#include "FileBoxController.h"
#include "FileWriter.h"
#include "FileReader.h"

FileBoxController::FileBoxController(
        WeaponsAndLifeController &wep_controller,
        std::shared_ptr<MapController> map_controller)
        : weapons_controller(wep_controller),
          map_controller(std::move(map_controller)) {
}

void FileBoxController::onSaveClicked() const {

    std::vector<std::vector<double>> worms;
    std::vector<std::vector<double>> girders;

    map_controller->getObjects(worms, girders);

    std::vector<int> weapons_ammo;
    unsigned int life;
    weapons_controller.getWeapons(weapons_ammo, life);

    FileWriter file("config_editor.yaml");
    file.save(weapons_ammo, worms,
              girders, life);
}

void FileBoxController::onLoadClicked() const {
    FileReader file("config_editor.yaml");
    std::vector<std::vector<double>> worms;
    std::vector<std::vector<double>> girders;
    std::vector<int> weps_ammo;
    unsigned int life;
    file.read(worms, girders,
              weps_ammo, life);

    weapons_controller.loadWeapons(weps_ammo, life);
    map_controller->loadObjects(worms, girders);
}


void FileBoxController::onNewClicked() const {
    weapons_controller.on_reset_clicked();
    map_controller->clean();
}


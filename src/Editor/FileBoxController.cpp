
#include "FileBoxController.h"
#include "FileWriter.h"
#include "FileReader.h"

FileBoxController::FileBoxController(
        const WeaponsListController &wep_controller,
        std::shared_ptr<MapController> map_controller)
        : weapons_controller(wep_controller),
          map_controller(std::move(map_controller)) {
}

void FileBoxController::onSaveClicked() const {
    std::vector<int> weapons_ammo;
    weapons_controller.getWeapons(weapons_ammo);

    std::vector<std::vector<double>> worms;
    std::vector<std::vector<double>> girders;
    map_controller->getObjects(worms, girders);

    FileWriter file("config_editor.yaml");
    file.save(weapons_ammo, worms, girders);
}

void FileBoxController::onLoadClicked() const {
    FileReader file("config_editor.yaml");
    std::vector<std::vector<double>> worms;
    std::vector<std::vector<double>> girders;
    std::vector<int> weps_ammo;
    file.read(worms, girders, weps_ammo);

    weapons_controller.loadWeapons(weps_ammo);
    map_controller->loadObjects(worms,girders);
}



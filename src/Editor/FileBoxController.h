
#ifndef WORMS_FILECONTROLLER_H
#define WORMS_FILECONTROLLER_H


#include "FileBoxView.h"
#include "WeaponsAndLifeController.h"
#include "MapController.h"

class FileBoxController {
private:
    WeaponsAndLifeController &weapons_controller;
    std::shared_ptr<MapController> map_controller;
    
public:
    FileBoxController(WeaponsAndLifeController &wep_controller,
                      std::shared_ptr<MapController> map_controller);

    void onSaveClicked() const;

    void onLoadClicked() const;

    void onNewClicked() const;
};


#endif //WORMS_FILECONTROLLER_H

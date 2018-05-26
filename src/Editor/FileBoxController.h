
#ifndef WORMS_FILECONTROLLER_H
#define WORMS_FILECONTROLLER_H


#include "FileBoxView.h"
#include "WeaponsAndLifeController.h"
#include "MapController.h"

class FileBoxController {
private:
    const WeaponsAndLifeController &weapons_controller;
    std::shared_ptr<MapController> map_controller;
public:
    FileBoxController(const WeaponsAndLifeController &controller,
                      std::shared_ptr<MapController> ptr);

    void onSaveClicked() const;

    void onLoadClicked() const;

};


#endif //WORMS_FILECONTROLLER_H

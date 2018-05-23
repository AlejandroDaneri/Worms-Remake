
#ifndef WORMS_FILECONTROLLER_H
#define WORMS_FILECONTROLLER_H


#include "FileBoxView.h"
#include "WeaponsListController.h"
#include "MapController.h"

class FileBoxController {
private:
    const WeaponsListController &weapons_controller;
    std::shared_ptr<MapController> map_controller;
public:
    FileBoxController(const WeaponsListController &controller,
                      std::shared_ptr<MapController> ptr);

    void onSaveClicked() const;

    void onLoadClicked() const;

};


#endif //WORMS_FILECONTROLLER_H

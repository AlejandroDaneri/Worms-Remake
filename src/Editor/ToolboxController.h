
#ifndef WORMS_TOOLBOXCONTROLLER_H
#define WORMS_TOOLBOXCONTROLLER_H


#include "Toolbox.h"

class ToolboxController {
private:
    Toolbox *toolbox;
    MapView *map;
public:
    ToolboxController(Toolbox *pToolbox);

    void clickedSignal(unsigned int id);

    void link_map(MapView *pMap);


};


#endif //WORMS_TOOLBOXCONTROLLER_H

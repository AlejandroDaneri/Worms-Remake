
#ifndef WORMS_TOOLBOXCONTROLLER_H
#define WORMS_TOOLBOXCONTROLLER_H


#include "ToolBoxView.h"

class ToolboxController {
private:
    ToolBoxView *toolbox;
    MapView *map;
public:
    ToolboxController(ToolBoxView *pToolbox);

    void clickedSignal(unsigned int id);

    void link_map(MapView *pMap);


};


#endif //WORMS_TOOLBOXCONTROLLER_H

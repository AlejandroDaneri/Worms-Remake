
#ifndef WORMS_TOOLBOXCONTROLLER_H
#define WORMS_TOOLBOXCONTROLLER_H


#include "editor_Toolbox.h"

class ToolboxController {
private:
    Toolbox* toolbox;
    Map *map;
public:
    ToolboxController(Toolbox *pToolbox);

    void clickedSignal(unsigned int id);

    void link_map(Map *pMap);


};


#endif //WORMS_TOOLBOXCONTROLLER_H

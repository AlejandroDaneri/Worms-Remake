
#include "editor_ToolboxController.h"

ToolboxController::ToolboxController(Toolbox *pToolbox)
        : toolbox(pToolbox)
{

}



void ToolboxController::link_map(Map *pMap) {
    this->map = pMap;
}

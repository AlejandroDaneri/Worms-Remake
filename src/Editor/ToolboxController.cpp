
#include "ToolboxController.h"

ToolboxController::ToolboxController(Toolbox *pToolbox)
        : toolbox(pToolbox) {

}


void ToolboxController::link_map(MapView *pMap) {
    this->map = pMap;
}

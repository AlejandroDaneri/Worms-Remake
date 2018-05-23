
#include "ToolboxController.h"

ToolboxController::ToolboxController(ToolBoxView *pToolbox)
        : toolbox(pToolbox) {

}


void ToolboxController::link_map(MapView *pMap) {
    this->map = pMap;
}

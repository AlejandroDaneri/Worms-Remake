
#ifndef WORMS_WEAPONCONTROLLER_H
#define WORMS_WEAPONCONTROLLER_H

#include "View/WeaponVieww.h"
#include "Model/WeaponModel.h"

class WeaponView;

class WeaponController {
private:
    std::shared_ptr<WeaponView> weapon_view;
    std::shared_ptr<WeaponModel> weapon_model;
public:
    WeaponController(std::shared_ptr<WeaponView>,
                     std::shared_ptr<WeaponModel>
                     model);

    void resetAmmo();

    void updateAmmo(int ammo);

    int getAmmo();
};


#endif //WORMS_WEAPONCONTROLLER_H

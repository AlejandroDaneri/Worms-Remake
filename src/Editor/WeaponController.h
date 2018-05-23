
#ifndef WORMS_WEAPONCONTROLLER_H
#define WORMS_WEAPONCONTROLLER_H


#include "WeaponBox.h"
#include "WeaponModel.h"

class WeaponBox;

class WeaponController {
private:
    std::shared_ptr<WeaponBox> weapon_view;
    std::shared_ptr<WeaponModel> weapon_model;
public:
    WeaponController(std::shared_ptr<WeaponBox>,
            std::shared_ptr<WeaponModel>
            model);

    void reset_ammo();

    void updateAmmo(double ammo);
};


#endif //WORMS_WEAPONCONTROLLER_H


#ifndef WORMS_WEAPONCONTROLLER_H
#define WORMS_WEAPONCONTROLLER_H


#include "editor_WeaponBox.h"
#include "editor_WeaponModel.h"

class WeaponBox;

class WeaponController {
private:
    WeaponBox &weapon_view;
    WeaponModel *weapon_model;
public:
    WeaponController(WeaponBox &View, WeaponModel *model);

    void reset_ammo();

    void updateAmmo(double ammo);
};


#endif //WORMS_WEAPONCONTROLLER_H

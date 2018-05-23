
#ifndef WORMS_WEAPONCONTROLLER_H
#define WORMS_WEAPONCONTROLLER_H


#include "editor_WeaponView.h"
#include "editor_WeaponModel.h"

class WeaponView;

class WeaponController {
private:
    std::shared_ptr<WeaponView> weapon_view;
    std::shared_ptr<WeaponModel> weapon_model;
public:
    WeaponController(std::shared_ptr<WeaponView>,
            std::shared_ptr<WeaponModel>
            model);

    void reset_ammo();

    void updateAmmo(double ammo);
};


#endif //WORMS_WEAPONCONTROLLER_H

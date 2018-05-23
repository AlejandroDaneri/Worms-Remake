
#ifndef WORMS_WEAPONMODEL_H
#define WORMS_WEAPONMODEL_H

//TODO: ver si puedo cambiarlo a weapon
class WeaponModel {
private:
    const int default_ammo;
    int actual_ammo;
public:
    explicit WeaponModel(const int &default_ammo);

    void reset_ammo();

    void set_ammo(const int &new_ammo);
};


#endif //WORMS_WEAPONMODEL_H


#ifndef WORMS_WEAPONMODEL_H
#define WORMS_WEAPONMODEL_H


class WeaponModel {
private:
    const int default_ammo;
    int actual_ammo;
public:
    explicit WeaponModel(int default_ammo);

    void reset_ammo();

    void set_ammo(int new_ammo);
};


#endif //WORMS_WEAPONMODEL_H


#ifndef WORMS_WEAPONMODEL_H
#define WORMS_WEAPONMODEL_H

//TODO: ver si puedo cambiarlo a weapon
class WeaponModel {
private:
    const int default_ammo;
    int actual_ammo;
public:
    explicit WeaponModel(const int &default_ammo);

    void resetAmmo();

    void setAmmo(const int &new_ammo);

    int getAmmo() const;
};


#endif //WORMS_WEAPONMODEL_H

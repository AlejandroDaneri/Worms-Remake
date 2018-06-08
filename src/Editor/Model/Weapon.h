
#ifndef WORMS_WEAPONMODEL_H
#define WORMS_WEAPONMODEL_H

// Clase que modela un arma
class Weapon {
private:
    const int default_ammo;
    int actual_ammo;
public:
    explicit Weapon(const int &default_ammo);

    // Establece el valor de la municion por defecto en el modelo
    void resetAmmo();

    // Establece el valor de la municion indicado en el modelo
    void setAmmo(const int &new_ammo);

    // Obtiene el valor actual de la municion
    int getAmmo() const;
};


#endif //WORMS_WEAPONMODEL_H

#include "Banana.h"
#include "WeaponNames.h"

Banana::Banana(int ammo) : DistanceWeapon(BANANA_NAME, ammo, true) {}

Banana::~Banana() {}

Banana::Banana(Banana&& other) : DistanceWeapon(std::move(other)) {}


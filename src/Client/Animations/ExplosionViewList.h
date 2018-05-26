#ifndef WORMS_EXPLOSIONVIEWLIST_H
#define WORMS_EXPLOSIONVIEWLIST_H

#include <unordered_map>
#include <memory>
#include "ExplosionView.h"

class ExplosionViewList {
    private:
        std::unordered_map<int, ExplosionView> animations;

        void check();

    public:
        ExplosionViewList();
        ~ExplosionViewList();

        void add(int id, ExplosionView&& animation);

        ExplosionView& at(int id);
};


#endif //WORMS_EXPLOSIONVIEWLIST_H

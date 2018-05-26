#ifndef WORMS_EXPLOSIONVIEWLIST_H
#define WORMS_EXPLOSIONVIEWLIST_H

#include <list>
#include "ExplosionView.h"

class ExplosionViewList {
    private:
        std::list<ExplosionView> animations;

        void check();

    public:
        ExplosionViewList();
        ~ExplosionViewList();

        void addAndStart(ExplosionView&& animation);

};


#endif //WORMS_EXPLOSIONVIEWLIST_H

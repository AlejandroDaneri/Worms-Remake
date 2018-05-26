#include "ExplosionViewList.h"

ExplosionViewList::ExplosionViewList() {}

ExplosionViewList::~ExplosionViewList() {}

void ExplosionViewList::check() {
    std::list<ExplosionView>::iterator iter;
    iter = this->animations.begin();
    while (iter != this->animations.end()) {
        if (iter->hasFinished()) {
            iter = this->animations.erase(iter);
        } else {
            ++iter;
        }
    }
}

void ExplosionViewList::addAndStart(ExplosionView&& animation) {
    this->check();
    this->animations.push_back(std::move(animation));
    this->animations.back().start();
}

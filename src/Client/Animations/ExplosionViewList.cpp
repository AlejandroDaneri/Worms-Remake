#include "ExplosionViewList.h"

ExplosionViewList::ExplosionViewList() {}

ExplosionViewList::~ExplosionViewList() {}

void ExplosionViewList::check() {
    std::unordered_map<int, ExplosionView>::iterator iter;
    iter = this->animations.begin();
    while (iter != this->animations.end()) {
        if (iter->second.hasFinished()) {
            iter = this->animations.erase(iter);
        } else {
            iter++;
        }
    }
}

void ExplosionViewList::add(int id, ExplosionView&& animation) {
    this->check();
    this->animations.insert(std::make_pair(id, std::move(animation)));
}

ExplosionView& ExplosionViewList::at(int id) {
    return this->animations.at(id);
}
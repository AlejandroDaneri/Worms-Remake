#include "ExplotionViewList.h"

ExplosionViewList::ExplosionViewList() {}

ExplosionViewList::~ExplosionViewList() {}

void ExplosionViewList::push_back(std::unique_ptr<ExplosionView>&& animation) {
	this->list.push_back(std::move(animation));
	this->list.back->start();
}

void ExplosionViewList::check() {
	std::vector<std::unique_ptr<ExplosionView>>::iterator iter = this->list.begin();
	while (iter != this->list.end()) {
		if (!(*iter)->isRunning()) {
			(*iter)->join();
			iter = this->list.erase(iter);
		} else {
			iter++;
		}
	}
}

int ExplosionViewList::size() {
	return this->list.size();
}

#include "fish.hpp"
#include "ocean.hpp"

Fish::Fish(int maxAge, int maxHunger) 
    : age_(0), hunger_(0), maxAge_(maxAge), maxHunger_(maxHunger), alive_(true),
      ocean_(nullptr), x_(0), y_(0) {}

void Fish::tick() {
    if (!alive_) return;
    ++age_;
    ++hunger_;
    if (age_ > maxAge_ || hunger_ > maxHunger_) {
        alive_ = false;
        return;
    }
    eat();
    move();
    reproduce();
}

bool Fish::isAlive() const {
    return alive_;
}

void Fish::setOcean(Ocean* ocean) {
    ocean_ = ocean;
}

void Fish::setPosition(size_t x, size_t y) {
    x_ = x;
    y_ = y;
}

std::pair<size_t, size_t> Fish::getPosition() const {
    return {x_, y_};
}
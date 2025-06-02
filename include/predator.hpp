#pragma once
#include "fish.hpp"
#include <string>

class PredatorFish : public Fish {
public:
    PredatorFish();

    std::string getType() const override;
    void tick() override;
    void draw(sf::RenderWindow& window, int cellSize) const override;

protected:
    void eat() override;
    void move() override;
    void reproduce() override;
};
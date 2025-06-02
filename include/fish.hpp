#pragma once
#include "entity.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class Ocean;

class Fish : public Entity {
public:
    Fish(int maxAge, int maxHunger);

    void tick() override;
    bool isAlive() const override;
    std::string getType() const override = 0;

    void setOcean(Ocean* ocean);
    void setPosition(size_t x, size_t y);
    std::pair<size_t, size_t> getPosition() const;
    virtual void draw(sf::RenderWindow& window, int cellSize) const = 0;

protected:
    virtual void eat() = 0;
    virtual void move() = 0;
    virtual void reproduce() = 0;

    int age_;
    int hunger_;
    int maxAge_;
    int maxHunger_;
    bool alive_;

    Ocean* ocean_;
    size_t x_, y_;
};
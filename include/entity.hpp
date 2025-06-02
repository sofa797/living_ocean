#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class Ocean;

class Entity {
public:
    virtual ~Entity() = default;

    virtual void tick() = 0;
    virtual bool isAlive() const = 0;
    virtual std::string getType() const = 0;

    virtual void setOcean(Ocean* ocean) = 0;
    virtual void setPosition(size_t x, size_t y) = 0;
    virtual void draw(sf::RenderWindow& window, int cellSize) const = 0;
};
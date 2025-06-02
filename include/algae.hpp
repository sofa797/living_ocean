#pragma once
#include "entity.hpp"
#include "ocean.hpp"
#include <memory>

class Algae : public Entity {
public:
    Algae();
    ~Algae();

    Algae(const Algae& other);
    Algae& operator=(const Algae& other);

    void tick() override;
    bool isAlive() const override;
    std::string getType() const override;
    void setOcean(Ocean* ocean);
    void setPosition(size_t x, size_t y);
    void draw(sf::RenderWindow& window, int cellSize) const override;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};
#include "herbivore.hpp"
#include "ocean.hpp"
#include "algae.hpp"
#include <iostream>
#include <cstdlib>
#include <iostream>

HerbivoreFish::HerbivoreFish() : Fish(20, 20) {}

std::string HerbivoreFish::getType() const {
    return "HerbivoreFish";
}

void HerbivoreFish::eat() {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = static_cast<int>(x_) + dx;
            int ny = static_cast<int>(y_) + dy;

            if (nx < 0 || ny < 0 ||
                nx >= static_cast<int>(ocean_->getWidth()) ||
                ny >= static_cast<int>(ocean_->getHeight()))
                continue;

            auto cell = ocean_->getCell(nx, ny);
            if (cell && cell->getType() == "Algae" && cell->isAlive()) {
                ocean_->setCell(nx, ny, nullptr);
                hunger_ = 0;
                std::cout << "HerbivoreFish at (" << x_ << "," << y_ << ") ate Algae at (" << nx << "," << ny << ")\n";
                return;
            }
        }
    }
}

void HerbivoreFish::move() {
    std::vector<std::pair<int,int>> freeCells;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = static_cast<int>(x_) + dx;
            int ny = static_cast<int>(y_) + dy;
            if (nx < 0 || ny < 0 ||
                nx >= static_cast<int>(ocean_->getWidth()) ||
                ny >= static_cast<int>(ocean_->getHeight()))
                continue;
            if (!ocean_->getCell(nx, ny))
                freeCells.push_back({nx, ny});
        }
    }
    if (!freeCells.empty()) {
        auto [nx, ny] = freeCells[rand() % freeCells.size()];
        ocean_->setCell(nx, ny, ocean_->getCell(x_, y_));
        ocean_->setCell(x_, y_, nullptr);
        x_ = nx;
        y_ = ny;
    }
}

void HerbivoreFish::reproduce() {
    if (age_ < 4 || hunger_ > maxHunger_ / 2 || rand() % 8 != 0)
        return;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = static_cast<int>(x_) + dx;
            int ny = static_cast<int>(y_) + dy;

            if (nx < 0 || ny < 0 ||
                nx >= static_cast<int>(ocean_->getWidth()) ||
                ny >= static_cast<int>(ocean_->getHeight()))
                continue;

            auto neighbor = ocean_->getCell(nx, ny);
            if (!neighbor || !neighbor->isAlive()) {
                auto baby = std::make_shared<HerbivoreFish>();
                baby->setOcean(ocean_);
                baby->setPosition(nx, ny);
                ocean_->setCell(nx, ny, baby);
                std::cout << "HerbivoreFish reproduced at (" << nx << "," << ny << ")\n";
                return;
            }
        }
    }
}

void HerbivoreFish::tick() {
    age_++;
    hunger_++;

    std::cout << "HerbivoreFish at (" << x_ << "," << y_ << ") age=" << age_ << " hunger=" << hunger_ << "\n";

    if (age_ > maxAge_ || hunger_ > maxHunger_) {
        alive_ = false;
        std::cout << "HerbivoreFish died at (" << x_ << "," << y_ << ")\n";
        ocean_->setCell(x_, y_, nullptr);
        return;
    }

    eat();
    move();
    reproduce();
}

void HerbivoreFish::draw(sf::RenderWindow& window, int cellSize) const {
    sf::CircleShape shape(cellSize / 100);
    shape.setFillColor(sf::Color::Blue);
    shape.setScale(0.5f, 0.5f);
    shape.setPosition(x_ * cellSize, y_ * cellSize);
    window.draw(shape);
}
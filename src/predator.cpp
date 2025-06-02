#include "predator.hpp"
#include "ocean.hpp"
#include <cstdlib>
#include <memory>
#include <iostream>

PredatorFish::PredatorFish() : Fish(30, 10) {}

std::string PredatorFish::getType() const {
    return "PredatorFish";
}

void PredatorFish::eat() {
    std::cout << "PredatorFish at (" << x_ << "," << y_ << ") tries to eat\n";

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = static_cast<int>(x_) + dx;
            int ny = static_cast<int>(y_) + dy;

            if (nx < 0 || ny < 0 || nx >= static_cast<int>(ocean_->getWidth()) || ny >= static_cast<int>(ocean_->getHeight()))
                continue;

            auto target = ocean_->getCell(nx, ny);
            if (target && target->getType() == "HerbivoreFish" && target->isAlive()) {
                if (target && target->getType() == "HerbivoreFish" && target->isAlive()) {
                    ocean_->setCell(nx, ny, nullptr);
                    hunger_ = 0;
                    return;
                }
                hunger_ = 0;
                return;
            }
        }
    }
}

void PredatorFish::move() {
    int dx = (rand() % 3) - 1;
    int dy = (rand() % 3) - 1;
    int nx = static_cast<int>(x_) + dx;
    int ny = static_cast<int>(y_) + dy;

    if (nx >= 0 && ny >= 0 && nx < static_cast<int>(ocean_->getWidth()) && ny < static_cast<int>(ocean_->getHeight())) {
        if (!ocean_->getCell(nx, ny)) {
            ocean_->setCell(nx, ny, ocean_->getCell(x_, y_));
            ocean_->setCell(x_, y_, nullptr);
            x_ = nx;
            y_ = ny;
        }
    }
}

void PredatorFish::reproduce() {
    if (age_ < 5 || hunger_ > maxHunger_ / 2 || rand() % 10 != 0)
        return;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = static_cast<int>(x_) + dx;
            int ny = static_cast<int>(y_) + dy;

            if (nx < 0 || ny < 0 || nx >= static_cast<int>(ocean_->getWidth()) || ny >= static_cast<int>(ocean_->getHeight()))
                continue;

            auto neighbor = ocean_->getCell(nx, ny);
            if (!neighbor || !neighbor->isAlive()) {
                auto baby = std::make_shared<PredatorFish>();
                baby->setOcean(ocean_);
                baby->setPosition(nx, ny);
                ocean_->setCell(nx, ny, baby);
                std::cout << "PredatorFish reproduced at (" << nx << "," << ny << ")\n";
                return;
            }
        }
    }
}

void PredatorFish::tick() {
    // std::cout << "PredatorFish tick at (" << x_ << ", " << y_ << ")\n";
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

void PredatorFish::draw(sf::RenderWindow& window, int cellSize) const {
    sf::CircleShape shape(cellSize / 100);
    shape.setFillColor(sf::Color::Red);
    shape.setScale(0.5f, 0.5f);
    shape.setPosition(x_ * cellSize, y_ * cellSize);
    window.draw(shape);
}
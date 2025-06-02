#include "algae.hpp"
#include "ocean.hpp"
#include <cstdlib>

struct Algae::Impl {
    int age = 0;
    bool alive = true;
    Ocean* ocean = nullptr;
    size_t x = 0;
    size_t y = 0;
};

Algae::Algae() : pimpl_(std::make_unique<Impl>()) {}

Algae::~Algae() = default;

Algae::Algae(const Algae& other)
    : pimpl_(std::make_unique<Impl>(*other.pimpl_)) {}

Algae& Algae::operator=(const Algae& other) {
    if (this != &other) {
        *pimpl_ = *other.pimpl_;
    }
    return *this;
}

void Algae::tick() {
    ++pimpl_->age;
    if (pimpl_->age > 10) {
        pimpl_->alive = false;
        return;
    }
    if (rand() % 6 != 0 || !pimpl_->ocean) return;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = static_cast<int>(pimpl_->x) + dx;
            int ny = static_cast<int>(pimpl_->y) + dy;

            if (nx < 0 || ny < 0 || nx >= static_cast<int>(pimpl_->ocean->getWidth()) ||
                ny >= static_cast<int>(pimpl_->ocean->getHeight())) {
                continue;
            }

            if (!pimpl_->ocean->getCell(nx, ny)) {
                auto newAlgae = std::make_shared<Algae>();
                newAlgae->setOcean(pimpl_->ocean);
                newAlgae->setPosition(nx, ny);
                pimpl_->ocean->setCell(nx, ny, newAlgae);
                return;
            }
        }
    }
}

bool Algae::isAlive() const {
    return pimpl_->alive;
}

std::string Algae::getType() const {
    return "Algae";
}

void Algae::setOcean(Ocean* ocean) {
    pimpl_->ocean = ocean;
}

void Algae::setPosition(size_t x, size_t y) {
    pimpl_->x = x;
    pimpl_->y = y;
}

void Algae::draw(sf::RenderWindow& window, int cellSize) const {
    sf::CircleShape shape(cellSize / 60);
    shape.setScale(0.5f, 0.5f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(pimpl_->x * cellSize, pimpl_->y * cellSize);
    window.draw(shape);
}
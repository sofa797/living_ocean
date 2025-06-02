#include "ocean.hpp"
#include <iostream>

Ocean::Ocean(size_t width, size_t height) 
    : width_(width), height_(height), grid_(width * height, nullptr) {}

size_t Ocean::index(size_t x, size_t y) const {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("Ocean coordinates out of range");
    }
    return y * width_ + x;
}

std::shared_ptr<Entity> Ocean::getCell(size_t x, size_t y) const {
    return grid_[index(x, y)];
}

void Ocean::setCell(size_t x, size_t y, std::shared_ptr<Entity> entity) {
    grid_[index(x, y)] = std::move(entity);
}

void Ocean::tick() {
    size_t count = 0;
    for (auto& cell : grid_) {
        if (cell && cell->isAlive()) {
            ++count;
            cell->tick();
        }
    }
    std::cout << "Ocean tick: " << count << " alive entities\n";
}

Ocean::Ocean(const Ocean& other)
    : width_(other.width_), height_(other.height_), grid_(other.grid_) {}

Ocean::Ocean(Ocean&& other) noexcept
    : width_(other.width_), height_(other.height_), grid_(std::move(other.grid_)) {}

Ocean& Ocean::operator=(const Ocean& other) {
    if (this == &other) return *this;
    width_ = other.width_;
    height_ = other.height_;
    grid_ = other.grid_;
    return *this;
}

Ocean& Ocean::operator=(Ocean&& other) noexcept {
    if (this == &other) return *this;
    width_ = other.width_;
    height_ = other.height_;
    grid_ = std::move(other.grid_);
    return *this;
}

Ocean::~Ocean() = default;

size_t Ocean::getWidth() const { return width_; }
size_t Ocean::getHeight() const { return height_; }
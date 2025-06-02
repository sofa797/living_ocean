#pragma once
#include "entity.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

class Ocean {
public:
    Ocean(size_t width, size_t height);
    void tick();
    std::shared_ptr<Entity> getCell(size_t x, size_t y) const;
    void setCell(size_t x, size_t y, std::shared_ptr<Entity> entity);

    size_t getWidth() const;
    size_t getHeight() const;

    Ocean(const Ocean& other);
    Ocean(Ocean&& other) noexcept;
    Ocean& operator=(const Ocean& other);
    Ocean& operator=(Ocean&& other) noexcept;
    ~Ocean();

private:
    size_t width_;
    size_t height_;
    std::vector<std::shared_ptr<Entity>> grid_;

    size_t index(size_t x, size_t y) const;
};
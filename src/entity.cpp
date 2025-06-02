#include "entity.hpp"
#include "ocean.hpp"
#include <cstdlib>

class Entity {
public:
    virtual ~Entity() = default;

    virtual void setOcean(Ocean* ocean) { this->ocean = ocean; }
    virtual void setPosition(size_t x, size_t y) { this->x = x; this->y = y; }
protected:
    Ocean* ocean = nullptr;
    size_t x = 0;
    size_t y = 0;
};
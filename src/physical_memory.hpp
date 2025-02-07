#ifndef PHYSICAL_MEMORY_HPP
#define PHYSICAL_MEMORY_HPP

#include "utils.hpp"
#include "frame.hpp"
#include <array>

class PhysicalMemory
{
private:
    std::array<Frame, FRAMES> memory;
public:
};

#endif
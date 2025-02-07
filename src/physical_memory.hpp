#ifndef PHYSICAL_MEMORY_HPP
#define PHYSICAL_MEMORY_HPP

#include "frame.hpp"
#include <array>

class PhysicalMemory
{
public:
    static constexpr int FRAMES = 256;

private:
    std::array<Frame, FRAMES> memory;

public:
};

#endif
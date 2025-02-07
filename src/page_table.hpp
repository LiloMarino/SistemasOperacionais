#ifndef PAGE_TABLE_HPP
#define PAGE_TABLE_HPP

#include "utils.hpp"
#include <array>

class PageTable
{
private:
    std::array<int, FRAME_SIZE> data;
public:
};

#endif
#ifndef TLB_HPP
#define TLB_HPP

#include "utils.hpp"
#include <array>

struct TLBMap
{
    int page_number;
    int frame_number;
};

class TLB
{
private:
    std::array<TLBMap, TLB_SIZE> data;
public:
};

#endif
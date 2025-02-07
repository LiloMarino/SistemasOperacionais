#ifndef TLB_HPP
#define TLB_HPP

#include <array>

struct TLBMap
{
    int page_number;
    int frame_number;
};

class TLB
{
public:
    static constexpr int TLB_SIZE = 16;

private:
    std::array<TLBMap, TLB_SIZE> data;

public:
};

#endif
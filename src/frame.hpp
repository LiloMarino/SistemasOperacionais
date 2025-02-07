#ifndef FRAME_HPP
#define FRAME_HPP

#include <array>

class Frame
{
public:
    static constexpr int FRAME_SIZE = 256;

private:
    std::array<char, FRAME_SIZE> data;

public:
};

#endif
#ifndef PAGE_TABLE_HPP
#define PAGE_TABLE_HPP

#include <array>

class PageTable
{
public:
    static constexpr int PAGES = 256;

private:
    std::array<int, PAGES> data;

public:
};

#endif
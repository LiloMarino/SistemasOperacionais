#include "page.hpp"

void Page::setPageNumber(int page_number)
{
    this->page_number = page_number;
}

std::array<char, Page::PAGE_SIZE> &Page::getData()
{
    return data;
}

bool Page::isEmpty()
{
    return page_number == -1;
}

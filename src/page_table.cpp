#include "page_table.hpp"
#include <iostream>
#include <iomanip>

void PageTable::addPage(int page_number, int frame_index)
{
    data[page_number].frame_index = frame_index;
    data[page_number].present = true;
}

void PageTable::removePage(int page_number)
{
    data[page_number].frame_index = 0;
    data[page_number].present = false;
}

int PageTable::getPage(int page_number)
{
    if (data[page_number].present)
    {
        return data[page_number].frame_index;
    }
    page_fault++;
    return -1;
}

int PageTable::getPageFault() const
{
    return page_fault;
}

void PageTable::printPageTable()
{
    std::cout << "###########" << std::endl;
    for (int i = 0; i < PAGES; i++)
    {
        std::cout << std::setw(4) <<  i << " - " << std::setw(4) << data[i].frame_index << " - " << (data[i].present ? "1" : "0") << std::endl;
    }
    std::cout << "###########" << std::endl;
}

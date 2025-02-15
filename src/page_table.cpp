#include "page_table.hpp"

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

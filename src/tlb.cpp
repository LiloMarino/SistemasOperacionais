#include "tlb.hpp"

TLB::TLB(ReplacementPolicy policy)
    : replacement_policy(policy) {}

void TLB::addPage(int page_number, int frame_index)
{
    int victim = replacement_policy(fifo_queue, access_counters);

    for (auto &entry : data)
    {
        if (entry.page_number == victim)
        {
            entry.page_number = page_number;
            entry.frame_index = frame_index;
            break;
        }
    }

    fifo_queue.push(page_number);
    access_counters[page_number] = timestamp++;
}

int TLB::getFrame(int page_number)
{
    if (access_counters.find(page_number) != access_counters.end())
    {
        access_counters[page_number] = timestamp++;
    }

    for (const auto &entry : data)
    {
        if (entry.page_number == page_number)
        {
            return entry.frame_index;
        }
    }

    return -1;
}

#include "tlb.hpp"

TLB::TLB(ReplacementPolicy policy)
    : replacement_policy(policy) {}

void TLB::addPage(int page_number, int frame_index)
{
    // Procura uma entrada livre para adicionar a nova entrada
    for (auto &entry : data)
    {
        if (entry.page_number == -1)
        {
            entry.page_number = page_number;
            entry.frame_index = frame_index;
            fifo_queue.push(page_number);
            access_counters[page_number] = timestamp++;
            return;
        }
    }

    // Se nenhuma entrada livre utiliza a política de substituição
    int remove = replacement_policy(fifo_queue, access_counters);
    for (auto &entry : data)
    {
        if (entry.page_number == remove)
        {
            entry.page_number = page_number;
            entry.frame_index = frame_index;
            fifo_queue.push(page_number);
            access_counters[page_number] = timestamp++;
            return;
        }
    }
}

int TLB::getFrame(int page_number)
{
    // Atualiza o tempo de acesso
    if (access_counters.find(page_number) != access_counters.end())
    {
        access_counters[page_number] = timestamp++;
    }

    // Procura a entrada
    for (const auto &entry : data)
    {
        if (entry.page_number == page_number)
        {
            return entry.frame_index;
        }
    }
    return -1;
}

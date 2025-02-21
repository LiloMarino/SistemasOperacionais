#include "physical_memory.hpp"

PhysicalMemory::PhysicalMemory(int num_frames, ReplacementPolicy policy)
    : memory(num_frames), replacement_policy(policy) {}

void PhysicalMemory::setPageRemoveCallback(std::function<void(int)> callback)
{
    on_page_remove = std::move(callback);
}

int PhysicalMemory::addPage(Page &&page)
{
    // Procura um quadro livre para adicionar a página
    for (int frame_index = 0; frame_index < memory.size(); frame_index++)
    {
        if (memory[frame_index].isEmpty())
        {
            memory[frame_index] = std::move(page);
            fifo_queue.push(frame_index);
            access_counters[frame_index] = timestamp++;
            return frame_index;
        }
    }

    // Se nenhum quadro estiver livre utiliza a política de substituição
    int frame_index = replacement_policy(fifo_queue, access_counters);
    on_page_remove(memory[frame_index].getPageNumber());
    memory[frame_index] = std::move(page);
    fifo_queue.push(frame_index);
    access_counters[frame_index] = timestamp++;
    return frame_index;
}

Frame &PhysicalMemory::getFrame(int index)
{
    access_counters[index] = timestamp++;
    return memory[index];
}

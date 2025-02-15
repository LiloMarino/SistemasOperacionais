#include "physical_memory.hpp"

PhysicalMemory::PhysicalMemory(int num_frames, ReplacementPolicy policy)
    : memory(num_frames), replacement_policy(policy) {}

void PhysicalMemory::setPageRemoveCallback(std::function<void(int)> callback)
{
    on_page_remove = std::move(callback);
}

int PhysicalMemory::addPage(Page &&page)
{
    int frame_index = replacement_policy(fifo_queue, access_counters);

    if (frame_index == -1)
    {
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i].isEmpty())
            {
                frame_index = i;
                break;
            }
        }
    }

    if (frame_index != -1)
    {
        memory[frame_index] = std::move(page);
        on_page_remove(frame_index);
        fifo_queue.push(frame_index);
        access_counters[frame_index] = timestamp++;
    }

    return frame_index;
}

Frame &PhysicalMemory::getFrame(int index)
{
    access_counters[index] = timestamp++;
    return memory[index];
}

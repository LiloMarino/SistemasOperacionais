#include "memory_manager.hpp"

MemoryManager::MemoryManager(std::ifstream &&backing_store, ReplacementPolicy policy, int num_frames)
    : backing_store(std::move(backing_store)), tlb(policy), physical_memory(num_frames, policy) {}

std::tuple<int, char> MemoryManager::getContent(int page_number, int offset)
{
    int physical_address;
    char content;

    return {physical_address, content};
}

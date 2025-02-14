#include "memory_manager.hpp"

MemoryManager::MemoryManager(std::ifstream &&backing_store)
    : backing_store(std::move(backing_store)) {}

char MemoryManager::getContent(int page_number, int offset)
{
}

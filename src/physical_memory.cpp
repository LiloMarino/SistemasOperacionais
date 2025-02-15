#include "physical_memory.hpp"

PhysicalMemory::PhysicalMemory(ReplacementPolicy policy)
    : replacement_policy(policy) {}
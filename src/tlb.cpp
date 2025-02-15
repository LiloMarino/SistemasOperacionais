#include "tlb.hpp"

TLB::TLB(ReplacementPolicy policy)
    : replacement_policy(policy) {}
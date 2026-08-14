#pragma once
#include <cstdint>

struct CacheLine {
    bool valid;
    uint64_t tag; // Upgraded to 64-bit to prevent silent bit-truncation
    uint32_t lru_counter;
    
    CacheLine() : valid(false), tag(0), lru_counter(0) {}
};
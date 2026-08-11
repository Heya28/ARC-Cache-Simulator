#pragma once
#include<cstdint>

struct CacheLine{
    bool valid;
    uint32_t tag; 
    uint32_t lru_counter;
    CacheLine(): valid(false), tag(0), lru_counter(0){}
};
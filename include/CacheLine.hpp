#pragma once
#include<cstdint>

struct CacheLine{
    bool valid;
    uint32_t tag; 
    CacheLine(): valid(false), tag(0){}
};
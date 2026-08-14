#pragma once
#include "CacheLine.hpp"
#include<vector>

class Cache {
private:
    std::vector<CacheLine> cache_lines; // 1D vector 
    uint32_t num_sets;
    uint32_t num_ways;
    uint32_t block_size; 
    uint64_t hits; 
    uint64_t misses;

public:
    Cache(uint32_t num_sets, uint32_t num_ways, uint32_t block_size);
    void access(uint64_t address);
    
    uint64_t get_hits() const { return hits; }
    uint64_t get_misses() const { return misses; }
};

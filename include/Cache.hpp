#pragma once
#include "CacheLine.hpp"
#include<vector>

class Cache {
private:
    uint32_t num_sets;
    uint32_t num_ways;
    uint32_t block_size;
    std::vector<CacheLine> cache_lines; // 1D vector num_sets*num_ways is the size. 
    uint64_t hits;
    uint64_t misses;
    uint64_t access_counter; // timestamp - the access number at which a cacheline was last used.

public:
    Cache(uint32_t num_sets, uint32_t num_ways, uint32_t block_size);
    bool access(uint64_t address);
    
    uint64_t get_hits() const { return hits; }
    uint64_t get_misses() const { return misses; }
};

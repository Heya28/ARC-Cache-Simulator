#pragma once
#include "AddressDecoder.hpp"
#include "Cache.hpp"
#include <unordered_set>

class MissClassifier{
    private:
    uint64_t compulsory_misses;
    uint64_t capacity_misses;
    uint64_t conflict_misses;
    uint64_t total_ways;
    uint32_t block_size;
    std::unordered_set<uint64_t> seen_blocks; // Cache A
    Cache cacheB;
    public:
    MissClassifier(uint64_t total_ways, uint32_t block_size);
    void classify(uint64_t address);
    uint64_t get_compulsory_misses() const { return compulsory_misses; }
    uint64_t get_capacity_misses() const { return capacity_misses; }
    uint64_t get_conflict_misses() const { return conflict_misses; }
};
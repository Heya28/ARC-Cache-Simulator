#pragma once
#include<cstdint>
#include<list>
#include<unordered_map>

class ARCCache{
    std::list<uint64_t> T1, T2, B1, B2;
    std::unordered_map<uint64_t, std::pair<std::list<uint64_t>*, std::list<uint64_t>::iterator>> location;
    uint32_t c; // total capacity of real cache aka num of cachelines
    uint32_t p; // parameter aka adaptive target size for T1
    uint64_t hits;
    uint64_t misses;
    uint32_t block_size;

    public:
    ARCCache(uint32_t capacity, uint32_t size_of_block); // capacity = num_sets*num_ways = c 
    bool access(uint64_t address);
    void insert_into_list(uint64_t tag, std::list<uint64_t>& list_name);
    void remove_from_list(uint64_t tag, std::list<uint64_t>& list_name);
    void replace();
    
    uint64_t get_hits() const { return hits; }
    uint64_t get_misses() const { return misses; }
};
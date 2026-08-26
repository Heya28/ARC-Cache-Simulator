#include "Cache.hpp"
#include "AddressDecoder.hpp"

Cache::Cache(uint32_t num_sets, uint32_t num_ways, uint32_t block_size)
    : num_sets(num_sets), 
      num_ways(num_ways), 
        block_size(block_size), 
      cache_lines(num_sets * num_ways),         
      hits(0), 
      misses(0), 
      access_counter(0) {}

void Cache::access(uint64_t address){
    uint32_t index= get_index(address, num_sets, block_size);
    uint64_t tag_address= get_tag( address, num_sets, block_size);
    uint32_t start_index=index*num_ways;
    access_counter++; // timestamp increases at every access.

    bool hitcheck=false;
    for(uint32_t i=start_index;i<start_index+num_ways;i++){
        // At set number = index, the block must be checked in this range for a hit/miss.
        if(cache_lines[i].valid){
            if(cache_lines[i].tag==tag_address){
                // Cache Hit 
                hits++;
                hitcheck=true;
                cache_lines[i].lru_counter=access_counter; 
                break;
            }
        }
    }
    if(!hitcheck){
        misses++;
        // Cache Miss
        // Check if there are any empty cachelines. 
        bool emptycacheline=false;
        for(uint32_t i=start_index;i<start_index+num_ways;i++){
            if(cache_lines[i].valid==0){
                // Insert block to empty cacheline. 
                cache_lines[i].tag=tag_address;
                cache_lines[i].valid=1;
                cache_lines[i].lru_counter=access_counter;
                emptycacheline=true;
                break;
            }
        }
        if(!emptycacheline){
            // Cache Miss but all cachelines in set are occupied. Need to evict Least Recently Used using lru_counter;
            uint32_t insertindex=start_index;
            uint64_t lru_access_time=cache_lines[insertindex].lru_counter;
            for(uint32_t i=start_index+1;i<start_index+num_ways;i++){
                if(cache_lines[i].lru_counter<lru_access_time){
                    insertindex=i;
                    lru_access_time=cache_lines[i].lru_counter;
                }
            }
            cache_lines[insertindex].lru_counter=access_counter;
            cache_lines[insertindex].tag=tag_address;
        }
    }
}
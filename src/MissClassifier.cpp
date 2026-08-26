#include "MissClassifier.hpp"

MissClassifier::MissClassifier(uint64_t total_ways, uint32_t block_size)
    : compulsory_misses(0),
      capacity_misses(0),
      conflict_misses(0),
      total_ways(total_ways), 
      block_size(block_size), 
      cacheB(1,total_ways,block_size) {}

void MissClassifier::classify(uint64_t address){
    uint64_t unique_tag_address = get_tag(address, 1, block_size);
    if(seen_blocks.find(unique_tag_address) == seen_blocks.end()){
        // Compulsory miss
        compulsory_misses++;
        seen_blocks.insert(unique_tag_address);
    }else{
        bool is_a_hit=cacheB.access(address);
        if(!is_a_hit){
            capacity_misses++;
        }else{
            conflict_misses++;
        }
    }
}
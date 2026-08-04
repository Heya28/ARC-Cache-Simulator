#include "Cache.hpp"
#include "AddressDecoder.hpp"

void access(Cache& cache, uint32_t address){
    // access() simulates one memory access 

    uint32_t index=get_index(address);
    uint32_t tag_check=get_tag(address);

    // Check if row is holding data ( valid bit ) & check if data is corresponding to address ( tag )
    if(cache.sets[index].valid && cache.sets[index].tag==tag_check){
        // Hit
        cache.hits++;
    }else{
        cache.misses++;
        // Direct mapped cache --> eviction of current row. Can cause conflict miss. 
        cache.sets[index].valid=true;
        cache.sets[index].tag=tag_check; 
    }
}
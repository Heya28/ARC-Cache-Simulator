#include "Cache.hpp"
#include "AddressDecoder.hpp"

void access(Cache& cache, uint64_t address){
    // access() simulates one memory access 

    uint32_t index = get_index(address, cache.num_sets, cache.block_size);
    uint64_t tag_check = get_tag(address, cache.num_sets, cache.block_size);

    // Check if row is holding data ( valid bit ) & check if data is corresponding to address ( tag )
    std::vector<CacheLine>& ways=cache.sets[index];
    bool flag=false; 
    int accessed_way=-1;
    for(int i=0;i<ways.size();i++){
        if((ways[i].valid) && (ways[i].tag==tag_check)){
            // Hit
            cache.hits++;
            accessed_way=i;
            flag=true;
            break;
        }
    }

    if(!flag){
        // Miss
        cache.misses++;
        bool empty_way=false;
        // Atleast one way is empty
        int recent_way=0;
        for(int i=0;i<ways.size();i++){
            if(!(ways[i].valid)){
                ways[i].tag=tag_check;
                ways[i].valid=true;
                recent_way=i;
                empty_way=true;
                break;
            }
        }
        
        if(!empty_way){
        // All ways are full ( LRU )
        int lru_way = 0;
        for(int i = 1; i < ways.size(); i++) {
            if(ways[i].lru_counter > ways[lru_way].lru_counter) {
                lru_way = i;
            }
        }
            ways[recent_way].tag=tag_check;
            ways[recent_way].valid=true;
        }
        // Incase of miss, all other ways have their lru_counters++ && the recent_way has lru_counter set to 0. 
        for(int k=0;k<ways.size();k++){
            if(k==recent_way){
                ways[k].lru_counter=0;
            }else{
                ways[k].lru_counter++;
            }
        }
    }else{
        // Incase of hit, all other ways have their lru_counters++
        for(int k=0;k<ways.size();k++){
            if(k==accessed_way){
                ways[k].lru_counter=0;
            }else{
                ways[k].lru_counter++;
            }
        }
    } 
}
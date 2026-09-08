#include "ARCCache.hpp"
#include "AddressDecoder.hpp"
#include<algorithm>

ARCCache::ARCCache(uint32_t capacity, uint32_t size_of_block) : c(capacity), p(c/2), hits(0), misses(0), block_size(size_of_block){}
// new/recently-touched items go to the front, oldest/least-recently-used sit at the back

void ARCCache::insert_into_list(uint64_t tag, std::list<uint64_t>& list_name){
    list_name.emplace_front(tag);
    location[tag]={&list_name, list_name.begin()};
}

void ARCCache::remove_from_list(uint64_t tag, std::list<uint64_t>& list_name){
    list_name.erase(location[tag].second); // erase() takes an iterator
    location.erase(tag);
}

// When T1 + T2 == c, If another block has to be put into cache, need to remove a current occupying cacheline.
void ARCCache::replace(){
    if(!(T1.empty()) && T1.size()>p){
        // Take T1's LRU end and insert into B1's MRU end
        uint64_t replaced_tag=T1.back();
        remove_from_list(replaced_tag,T1);
        insert_into_list(replaced_tag,B1);
    }else{
        // Take T2's LRU end and insert into B2's MRU end
        uint64_t replaced_tag=T2.back();
        remove_from_list(replaced_tag,T2);
        insert_into_list(replaced_tag,B2);
    }
}

bool ARCCache::access(uint64_t address){
    uint64_t unique_tag_address = get_tag(address, 1, block_size);
    // Check if tag in either T1 or T2 or B1 or B2
    auto check_it=location.find(unique_tag_address);
    if(check_it!=location.end()){
        if(check_it->second.first==&T1 || check_it->second.first==&T2 ){
            // Case 1: Block is in T1 or T2
            hits++;
            return true;
        }
        misses++;
        // Case 2: Block is in B1
        if(check_it->second.first==&B1){
            p=std::min(c,p+1);
            if((uint32_t)T1.size()+(uint32_t)T2.size()==c){
                // cache cannot accomodate the new block without removing a currently held block. 
                replace(); // remove a currently occupying LRU block from T1 or T2
            }
            remove_from_list(unique_tag_address, B1);
            insert_into_list(unique_tag_address, T2);
        }
        // Case 3: Block is in B2
        if(check_it->second.first==&B2){
            p=std::max(0u,p-1);
            if((uint32_t)T1.size()+(uint32_t)T2.size()==c){
                // cache cannot accomodate the new block without removing a currently held block. 
                replace(); // remove a currently occupying LRU block from T1 or T2
            }
            remove_from_list(unique_tag_address, B2);
            insert_into_list(unique_tag_address, T2);
        }
        return false;
    }
    
    // Case 4: Block is not in T1 or T2 or B1 or B2 - first time being accsessed. 
    // Ghost-list check; independent of whether the real cache is full.
    if ((uint32_t)T1.size() + (uint32_t)B1.size() == c && !B1.empty()) {
        uint64_t deleted_tag=B1.back();
        remove_from_list(deleted_tag,B1);
    }
    if ((uint32_t)T1.size() + (uint32_t)T2.size() + (uint32_t)B1.size() + (uint32_t)B2.size() >= 2*c && !B2.empty()) {
        uint64_t deleted_tag=B2.back();
        remove_from_list(deleted_tag,B2);
    }

    // If cache is full, evict the LRU block from T1 or T2 as per parameter p
    if ((uint32_t)T1.size() + (uint32_t)T2.size() == c) {
        replace();
    }

    // insert the brand-new tag into T1 (seen once).
    insert_into_list(unique_tag_address, T1);
    misses++;
    return false;
}
   

#include "Cache.hpp"
#include "AddressDecoder.hpp"
#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>

int main(){
    Cache cache(64, 4, 64);  // 64 sets, 4-way, 64-byte blocks
    // Open File
    std::ifstream file("traces/trace.txt");
    if(!file.is_open()) {
        std::cout << "File not found\n";
        return 1;
    }
    std::string line;

    // Parse each line
    while(getline(file,line)){
        char operation; // R or W
        uint64_t address; 
        sscanf(line.c_str(), "%c %lx", &operation, &address); 
        // Call for each memory trace
        cache.access(address);
    }
    // Print results
    float hit_ratio = static_cast<float>(cache.get_hits()) / (cache.get_hits() + cache.get_misses());
    float hit_percent=hit_ratio*100.0;
    std::cout<<"Number of Hits   : "<<cache.get_hits()<<"\n";
    std::cout<<"Number of Misses : "<<cache.get_misses()<<"\n";
    std::cout<< "Hit Rate        : " << hit_percent << "%\n";
}

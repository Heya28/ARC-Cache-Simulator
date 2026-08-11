#include "Cache.hpp"
#include "AddressDecoder.hpp"
#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>

int main(){
    Cache cache(64,1); // 64 sets 4 way associative 
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
        uint32_t address; 
        sscanf(line.c_str(),"%c %x", &operation, &address);
        // Call for each memory trace
        access(cache, address);
    }
    // Print results
    float hit_ratio=float(cache.hits)/float(float(cache.hits)+float(cache.misses));
    float hit_percent=hit_ratio*100.0;
    std::cout<<"Number of Hits   : "<<cache.hits<<"\n";
    std::cout<<"Number of Misses : "<<cache.misses<<"\n";
    std::cout<< "Hit Rate        : " << hit_percent << "%\n";

}

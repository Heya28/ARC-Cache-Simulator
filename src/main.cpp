#include "Cache.hpp"
#include "AddressDecoder.hpp"
#include "MissClassifier.hpp"
#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>

int main(){
    Cache cacheC(64, 4, 64);  // 64 sets, 4-way, 64-byte blocks
    MissClassifier missclassifier(64*4, 64);
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
        bool is_a_hit=cacheC.access(address);
        if(!is_a_hit){
            // missclassifier does not take cachec into reference so only call when it is a cache miss.
            missclassifier.classify(address);
        }
    }
    // Print results
    float hit_ratio = static_cast<float>(cacheC.get_hits()) / (cacheC.get_hits() + cacheC.get_misses());
    float hit_percent=hit_ratio*100.0;
    std::cout<<"Number of Hits   : "<<cacheC.get_hits()<<"\n";
    std::cout<<"Number of Misses : "<<cacheC.get_misses()<<"\n";
    std::cout<<"Number of Compulsory Misses : "<<missclassifier.get_compulsory_misses()<<"\n";
    std::cout<<"Number of Capacity Misses : "<<missclassifier.get_capacity_misses()<<"\n";
    std::cout<<"Number of Conflict Misses : "<<missclassifier.get_conflict_misses()<<"\n";
    std::cout<< "Hit Rate        : " << hit_percent << "%\n";
    uint64_t num_misses_check=(missclassifier.get_compulsory_misses()+missclassifier.get_capacity_misses()+missclassifier.get_conflict_misses());
    if(num_misses_check==cacheC.get_misses()){
        std::cout<<"Classifier pass";
    }else{
        std::cout<<"Classifier fail";
    }
}

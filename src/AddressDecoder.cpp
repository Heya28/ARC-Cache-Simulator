#include "AddressDecoder.hpp"

uint32_t log2_exact(uint32_t n) {
    // for floating - point precision errors in log2 (cmath function)
    uint32_t bits = 0;
    while (n > 1) {
        n >>= 1;
        bits++;
    }
    return bits;
} 

uint32_t get_index(uint32_t address, uint32_t num_sets, uint32_t block_size) {
    uint32_t offset_bits = log2_exact(block_size);
    uint32_t index_bits  = log2_exact(num_sets);
    uint32_t index  = (address >> offset_bits) & ((1 << index_bits) - 1);
    return index;
}

uint32_t get_tag(uint32_t address, uint32_t num_sets, uint32_t block_size) {
    uint32_t offset_bits = log2_exact(block_size);
    uint32_t index_bits  = log2_exact(num_sets);
    uint32_t tag = address >> (offset_bits + index_bits);
    return tag;
}

uint32_t get_offset(uint32_t address, uint32_t block_size){
    uint32_t offset_bits=log2_exact(block_size);
    uint32_t offset = address & ((1 << offset_bits) - 1);
    return offset;
}
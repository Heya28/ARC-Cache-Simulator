#include "AddressDecoder.hpp"

uint32_t log2_exact(uint32_t n) {
    // compiler intrinsic (GCC/Clang) and requires no special headers or C++20 support.
    // Maps directly to hardware trailing-zero count (tzcnt) in 1 clock cycle.
    return __builtin_ctz(n);
}

uint32_t get_index(uint64_t address, uint32_t num_sets, uint32_t block_size) {
    uint32_t offset_bits = log2_exact(block_size);
    uint32_t index_bits  = log2_exact(num_sets);
    uint32_t index  = (address >> offset_bits) & ((1ULL << index_bits) - 1);
    return index;
}

uint64_t get_tag(uint64_t address, uint32_t num_sets, uint32_t block_size) {
    uint32_t offset_bits = log2_exact(block_size);
    uint32_t index_bits  = log2_exact(num_sets);
    uint64_t tag = address >> (offset_bits + index_bits);
    return tag;
}

uint32_t get_offset(uint64_t address, uint32_t block_size){
    uint32_t offset_bits = log2_exact(block_size);
    uint32_t offset = address & ((1ULL << offset_bits) - 1);
    return offset;
}
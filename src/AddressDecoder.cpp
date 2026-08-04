#include "AddressDecoder.hpp"

uint32_t get_index(uint32_t address) {
    return (address >> 6) & 0x3F; // shift 6 bits and bitmask
}

uint32_t get_tag(uint32_t address) {
    return address >> 12; // shift 12 bits 
}

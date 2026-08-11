#pragma once
#include <cstdint>

uint32_t get_index(uint32_t address, uint32_t num_sets, uint32_t block_size);
uint32_t get_tag(uint32_t address, uint32_t num_sets, uint32_t block_size);
uint32_t get_offset(uint32_t address, uint32_t block_size);
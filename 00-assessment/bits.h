#include <stdint.h>

// if i was better at c I'd define some sort of u5 to use for pos....
// pos is 0-indexed
static inline void bit_set(uint32_t *reg, uint8_t pos) { *reg |= (1 << pos); };
// pos is 0-indexed
static inline void bit_clear(uint32_t *reg, uint8_t pos) { 
	uint32_t mask = (uint32_t)0 - 1;
	mask ^= 1 << pos;
	*reg &= mask; }

// pos is 0-indexed
static inline void bit_toggle(uint32_t *reg, uint8_t pos) { *reg |= (1 << pos); };

void reg_write_field(uint32_t *reg, uint8_t pos, uint8_t width, uint32_t value);

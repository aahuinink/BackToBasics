/* ### C2. Bit set/clear/toggle/read on a 32-bit register, plus `reg_write_field(reg, pos, width, value)` (file: `bits.h`)

Notes: macros or `static inline` functions? Why?

>   Not sure, but I can do this.
*/

#include "bits.h"
#include <stdint.h>

static inline uint32_t ones_mask_at_pos(uint8_t pos, uint8_t width);
static inline uint32_t zeroes_mask_at_pos(uint8_t pos, uint8_t width);
static inline uint32_t masked_value_in_position(uint32_t value, uint8_t pos, uint8_t width);

// writes the bits in value to a register, where:
//		reg is the register to write to
//		pos is the index of the LEAST SIGNIFICANT BIT
//		width is the number of bits of value to write, starting reg [pos + width], ending at reg[pos].
//				note: the bits of value are not indexible. if the significance of value
//				exceeds what can be represented in width bits, then the more significant bits will be truncated
void reg_write_field(uint32_t *reg, uint8_t pos, uint8_t width, uint32_t value) {
	// create temp copy of reg to modify
	uint32_t temp = *reg;
	// clear bits at that position
	temp &= zeroes_mask_at_pos(pos, width);
	// write new value to that position
	temp |= masked_value_in_position(value, pos, width);

	*reg = temp;
}

static inline uint32_t masked_value_in_position(uint32_t value, uint8_t pos, uint8_t width) {
	return ( value << pos ) & ones_mask_at_pos(pos, width);
}

// provides a contiguous block of 1s of size width, ending at pos. all 0s otherwise
static inline uint32_t ones_mask_at_pos(uint8_t pos, uint8_t width) {
	return ( ( 0x1 << width ) - 1 ) << pos;
}
// provides a contiguous block of 0s of size width, ending at pos. all 1s otherwise
static inline uint32_t zeroes_mask_at_pos(uint8_t pos, uint8_t width) {
	return ( (uint32_t)0 - 1 ) ^ ones_mask_at_pos(pos, width);
}

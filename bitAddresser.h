/**
 * Romeo Jung
 * Timothy Lo
 * 
 * bitAddresser.h
 */

# include "libfiles.h"

static inline uint8_t get(uint16_t number, uint8_t index)
{
	return (number >> (15 - index) & 1);
}

static inline uint8_t get32(uint32_t number, uint8_t index)
{
	return (number >> (31 - index) & 1);
}

static inline void set(uint16_t *number, uint8_t index)
{
	(*number) = (*number) | (1 << (15 - index)) ; 
}

static inline void clr(uint16_t *number, uint8_t index)
{
	(*number) = (*number) & (MAXTOP ^ (1 << (15 - index)));
}


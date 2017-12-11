/**
 * Romeo Jung
 * Timothy Lo
 *
 * 12/10/2017
 *
 * IOtester.h
 *
 * supplemental .h file to .c
 * for testing the things in IOtester.c
 *
 * created by Romeo, written by Tim
 */

# ifndef _IOTESTER_H
# define _IOTESTER_H

# include "libfiles.h"

# ifndef MAXTOP
# define MAXTOP 65535
# endif

/** ================== static inline function ================== **/

static inline uint16_t parse(uint32_t buffer, uint8_t cursor)
{
	uint16_t charBuffer = (buffer >> (32 - (cursor + 16)));
	charBuffer &= MAXTOP;
	return charBuffer;

}

static inline uint32_t stitch(uint32_t preEx, uint8_t newBits)
{
	preEx = preEx << 8;
	preEx = preEx | (uint32_t)newBits;

	return preEx;
}

static inline uint8_t get(uint16_t number, uint8_t index)
{
	return (number >> (15 - index) & 1);
}

static inline void setbit(uint16_t *number, uint8_t index)
{
	(*number) = (*number) | (1 << (15 - index)) ; 
}

static inline void clrbit(uint16_t *number, uint8_t index)
{
	(*number) = (*number) & (MAXTOP ^ (1 << (15 - index)));
}


# endif


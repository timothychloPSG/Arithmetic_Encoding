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


# endif


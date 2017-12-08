/*
 * Romeo Jung
 * Timothy Lo
 *
 * 12/7/2017
 *
 * AR.h 
 *
 * the header file
 * for AR.c.
 * it includes a static inline function
 * and the various libraries.
 *
 * written by Romeo
 * debugged by Tim
 *
 */

# ifndef _AR_H
# define _AR_H

# include "libfiles.h"
# include "coder.h"
# include "model.h"

/**
 * calcRange function.
 *
 * calculates the new
 * top and bottom for encode
 * and decode.
 *
 * whether if it's top or bottom
 * depends on acc, which is
 * just the accumulated count
 * for the character.
 *
 * @param top the top
 * @param bot the bottom
 * @param total the total number of 
 * characters in the array
 * @papram acc the accumulated top
 * or bottom
 *
 * @return new top or bottom
 *
 */
static inline uint16_t calcRange(uint8_t top, uint8_t bot, uint32_t total, uint32_t acc)
{
	top = top + 1;				// since we're converting it to "actual numbers"
						// for range calculations.
	uint32_t diff = top - bot;		// take the difference (the range)
	diff *= acc;				// multiply it by the accumulated 
	diff = Math.ceil(diff/total);		// divide by the total count of the characters
	diff += bot;				// and add the bottom back in for actual range.

	return (uint16_t) diff;
}

# endif


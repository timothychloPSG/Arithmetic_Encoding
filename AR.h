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


//** =============== function headers ================= **//

void encode(Model *, FILE *, char, uint8_t *, uint8_t *);
void cleanup(Model *, FILE *);
char decode(Model *, uint32_t, uint8_t *, uint8_t *);


//** =============== static inlines ==================== **//

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
static inline uint16_t calcRange(uint16_t top, uint16_t bot, uint32_t total, uint32_t acc)
{
	uint32_t numberTop = top + 1;		// since we're converting it to "actual numbers"

	// printf("\n\n\n\t\t\ttop : %d\n\t\t\tbot: %d\n\t\t\tacc: %d\n\n\n\n", numberTop, bot, acc);
						// for range calculations.
	float diff = numberTop - bot;		// take the difference (the range)

	diff *= acc;				// multiply it by the accumulated

	diff = ceil(diff/total);		// divide by the total count of the characters

	diff += bot;				// and add the bottom back in for actual range.

	// printf("\n\n%f\n\n", diff);

	return (uint16_t) diff;
}

# endif


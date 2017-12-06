/**
 * Romeo Jung
 * Timothy Lo
 * 
 * coder.h
 * 
 * the headerfile that
 * contains the struct itself
 * and all the static inline
 * functions for coder.
 *
 * the coder includes top, bottom,
 * counter for pending bits, and
 * keeps track of the block for output. 
 *
 **/

# include "libfiles.h"

# ifndef _CODER_H
# define _CODER_H

# ifndef _TOPBOT_TRUEFALSE			// most of these defines are
# define TOP true 				// for functions that require a 
# define BOT false 				// certain boolean to work. 
# endif 					// it's better suited for the context understanding.

# ifndef _BLOCK_SETCLEAR
# define SET true
# define CLR false
# endif

# ifndef MAXTOP					// signifies that since we're working with 16 bit top's
# define MAXTOP (uint16_t)65535			// and bottoms, the largest number is 65535.
# endif

typedef struct Range coder;

struct Range
{
	uint16_t top;				// Holds the top bits 
	uint16_t bot;				// Holds the bottom bits
	uint16_t pendingBits;			// number of pending bits
	uint32_t block;				// blocks 32 bits at a time to the output
	uint32_t space;				// How much space is left for bits in the block
} ;


/**
 * newCoder function.
 *
 * malloc's a new struct for usage.
 *
 * @return code the coder made.
 */
static inline coder *newCoder()
{
	coder * code = (coder *)(malloc(sizeof(coder)));
	code->top = MAXTOP;
	code->bot = 0;
	code->pendingBits = 0;
	code->block = 0;
	code->space = 32;
	return code;
}

/**
 * delCoder function.
 *
 * deletes a given coder.
 *
 * @param *code the malloc'd instance of the coder
 */
static inline void delCoder(coder *code)
{
	free(code);
}

/**
 * getBit function.
 *
 * gets bit from either top or the bottom.
 * the TOP/BOTTOM define is used for when 
 * this function is called.
 *
 * @param top, bottom, index of the bit, and code struct
 * @return uint8_t the bit
 */
static inline uint8_t getBit(bool top, uint8_t index, coder *code)
{
	if (top)
	{
		return (code->top >> (3 - code->space) & 1);
	}
	else
	{
		return (code->bot >> (3 - code->space) & 1);
	}
}

static inline void set(bool top, uint8_t index, coder *code)
{
	if (top)
	{
		code -> top |= (1 << (15 - index));
	}
	else
	{
		code -> bot |= (1 << (15 - index));
	}
}

static inline void clr(bool top, uint8_t index, coder *code)
{
	if (top)
	{
		code -> top &= (MAXTOP ^ (1 << (15 - index)));
	}
	else
	{
		code -> bot &= (MAXTOP ^ (1 << (15 - index)));
	}
}

static inline void chBlock (bool sett, coder *code)
{
	if (code-> space < 1)
	{
		code -> space = 32;
		code -> block = 0;
	}
	if (sett)
	{
		code -> block |= ( 1 << (code->space - 1));
	}
	else
	{
		code -> block &= (MAXTOP ^ (code->space - 1));
	}
	(code -> space)-=1;
}
# endif

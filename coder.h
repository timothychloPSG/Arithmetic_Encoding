/*
Romeo Jung
Timothy Lo

coder.h
*/

# ifndef _CODER_H
# define _CODER_H

# ifndef _TOPBOT_TRUEFALSE
# define TOP true 
# define BOT false 
# endif 

# ifndef _BLOCK_SETCLEAR
# define SET true
# define CLR false
# endif

# ifndef MAXTOP
# define MAXTOP (uint16_t)65536
# endif

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>

typedef struct Range coder;

struct Range
{
	uint16_t top;				// Holds the top bits 
	uint16_t bot;				// Holds the bottom bits
	uint16_t pendingBits;		// Save the pending bits for later
	uint32_t block;				// Used for the output of bits to the output file
	uint32_t space;				// How many bits have been encoded into the block
} ;

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

static inline void delCoder(coder *code)
{
	free(code);
}

static inline uint8_t getBit(bool top, uint8_t space, coder *code)
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

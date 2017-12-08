/*
Romeo Jung
Timothy Lo

coder.h
*/

# include "libfiles.h"

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

typedef struct Range Coder;

struct Range
{
	uint16_t top;				// Holds the top bits 
	uint16_t bot;				// Holds the bottom bits
	uint16_t pendingBits;		// Save the pending bits for later
	uint32_t block;				// Used for the output of bits to the output file
	uint32_t space;				// How many bits have been encoded into the block
} ;

void updateStatus(Coder *);

static inline Coder *newCoder()
{
	Coder *code = (Coder *)(malloc(sizeof(Coder)));
	code->top = MAXTOP;
	code->bot = 0;
	code->pendingBits = 0;
	code->block = 0;
	code->space = 32;
	return code;
}

static inline void delCoder(Coder *code)
{
	free(code);
}

static inline uint8_t getBit(bool top, uint8_t index, Coder *code)
{
	if (top)
	{
		return (code->top >> (3 - index) & 1); 	//	Ask later on if the space in parameters is to be used for code->space
	} 
	else
	{
		return (code->bot >> (3 - index) & 1);
	}
}

static inline void set(bool top, uint8_t index, Coder *code)
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

static inline void clr(bool top, uint8_t index, Coder *code)
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

static inline void chBlock (bool sett, Coder *code)
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

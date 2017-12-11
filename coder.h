/*
 * Romeo Jung
 * Timothy Lo
 *
 * 12/7/2017
 *
 * coder.h
 *
 * is the .h file
 * to be included in 
 * coder.c
 *
 * contains the structure an d
 * the basic static inline functions.
 *
 * written by Romeo
 * debugged by Tim
 *
 */

# ifndef _CODER_H
# define _CODER_H

/** ================================= includes & defines ============================ **/

# include "libfiles.h"

# ifndef _TOPBOT_TRUEFALSE				// for set and clear functions to make more sense
# define TOP true 					// reading wise.
# define BOT false 
# endif 

# ifndef _BLOCK_SETCLEAR				// this is for chBlock function
# define SET true
# define CLR false
# endif

# ifndef MAXTOP						// for setting top as all 1's when
# define MAXTOP (uint16_t)65535				// we have a 16 bit number
# endif

typedef struct Range Coder;					

struct Range
{
	uint16_t top;					// the top 
	uint16_t bot;					// the bottom
	uint16_t pending;				// pending bits
	uint8_t block;					// block for blockifying output
							// we decided the output should be readable characters.
	uint32_t space;					// space left on the block out of 32
} ;

/** ================ function headers ====================== **/

void updateStatus(Coder *, FILE *, uint8_t *, uint8_t *);
void printStatus(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, bool, uint16_t, uint8_t, uint8_t);

/** =============== static inline functions ================ **/

/**
 * newCoder function.
 *
 * malloc's a new coder struct
 * and returns the pointer.
 *
 * I know I could have just declared
 * coder as a pointer struct of range
 * but I get really worried if I know
 * there are malloc'd structs but there
 * aren't pointer symbols with them...
 * I'd rather be constantly reminded that
 * they're malloc'd
 *
 * @return code the newly created coder
 * struct
 *
 */
static inline Coder *newCoder()
{
	Coder *code = (Coder *)(malloc(sizeof(Coder)));
	code->top = MAXTOP;
	code->bot = 0;
	code->pending = 0;
	code->block = 0;
	code->space = 8;
	return code;
}

/**
 * delCoder function.
 *
 * takes a pointer of the coder
 * and deletes it by freeing it.
 *
 * @param code the coder to be freed
 *
 */
static inline void delCoder(Coder *code)
{
	free(code);
}

/**
 * getBit function.
 *
 * gets the bit from either top or bottom.
 *
 * @param top the boolean for notifying
 * either top or bottom
 *
 * @param index the index of the bit.
 * the bit itself is read left to right
 * instead of right to left.
 * I think it's little endian??
 *
 * @param code the coder struct to 
 * read it from
 *
 * @return the bit read
 *
 * 
 */
static inline uint8_t getBit(bool top, uint8_t index, Coder *code)
{
	if (top)							// the define statement for TOP and BOT exist for this
	{								// actually, for the next few functions too
		return (code->top >> (15 - index) & 1);			// wrap it around since we're reading left to right
	} 
	else
	{
		return (code->bot >> (15 - index) & 1);
	}
}

/**
 * set function.
 *
 * sets a bit on either top or bottom.
 *
 * @param top a boolean for top or bottom
 * 
 * @param index the index of the bit trying
 * to set. read left to right. 
 *
 * @param code the coder struct to set it on
 *
 */
static inline void set(bool top, uint8_t index, Coder *code)
{
	if (top)
	{
		(code -> top) |= (1 << (15 - index));
	}
	else
	{
		(code -> bot) |= (1 << (15 - index));
	}
}

/**
 * clr function.
 *
 * clears a bit on either top or bottom.
 *
 * @param top the bool
 *
 * @param index the index of the bit
 * 
 * @param code the coder struct
 *
 */
static inline void clr(bool top, uint8_t index, Coder *code)
{
	if (top)
	{
		(code->top) &= (MAXTOP ^ (1 << (15 - index)));
	}
	else
	{
		(code -> bot) &= (MAXTOP ^ (1 << (15 - index)));
	}
}

/**
 * chBlock function.
 *
 * either clears or sets
 * a bit on the block.
 *
 * the SET and CLR macros
 * are made for this.
 *
 * @param sett the variable
 * for set and clear
 *
 * @param f for output file
 *
 * @param code the coder
 * struct.
 *
 * Has to include file *f later for writing
 *
 */
static inline void chBlock (bool sett, FILE *f, Coder *code)
{

	if (code-> space < 1)							// if there are no more spaces left
	{

		if(f != NULL)
		{
			fwrite(&(code->block), sizeof(uint8_t), 1, f);			// write block to file
		}

		(code->space) = 8;						// reset block space to 8
		(code->block) = 0;						// reset block to 0
	}

	if (sett)								// for setting the bit
	{
		(code->block) = (code->block) | (1 << (code->space - 1));	
	}
	else									// for clearing the bit
	{
		(code->block) = (code->block) & (MAXTOP ^ (code->space - 1));
	}

	(code -> space)-=1;							// we have one less space on the block.
}

# endif



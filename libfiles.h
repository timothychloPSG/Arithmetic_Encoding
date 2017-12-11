/**
 * Romeo Jung and Timothy Lo
 *
 * 12/7/2017
 *
 * libfiles.h
 *
 * This header files contains all the necessary header files for encoding/decoding
 */

# ifndef _LIBFILES_H
# define _LIBFILES_H

# include <math.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>

# include <errno.h>
# include <string.h>
# include <ctype.h>
# include <getopt.h>

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

static inline uint8_t get(uint16_t number, uint8_t index)
{
	return (number >> (15 - index) & 1);
}

static inline uint8_t get32(uint32_t number, uint8_t index)
{
	return (number >> (31 - index) & 1);
}

static inline void setBit(uint16_t *number, uint8_t index)
{
	(*number) = (*number) | (1 << (15 - index)) ; 
}

static inline void clrBit(uint16_t *number, uint8_t index)
{
	(*number) = (*number) & (MAXTOP ^ (1 << (15 - index)));
}

# endif
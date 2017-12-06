/*
Timothy lo
Romeo Jung

AR.h
*/

# ifndef _AR_H
# define _AR_H

// Dont forget to put libraries and other io functions in here that are necessary for main
static inline uint8_t calcRange(uint8_t top, uint8_t bot, uint32_t total, uint32_t segTopBot)
{
	uint32_t diff = top - bot;
	diff *= segTopBot;
	diff = Math.ceil(diff/total);
	diff += bot;
	return (uint8_t) diff;
}
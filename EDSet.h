/*
Romeo Jung 
Timothy Lo

EDset.h
*/

# ifndef _EDSET_H_
# define _EDSET_H_
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>


typedef struct EDset
{
	coder * code;
	uint32_t * freq;
	uint32_t total;
} EDset;

static inline void delEDset(EDset *d)
{
	delCoder(d->code);
	free(d->freq);
	free(d);
}

void updateRange(EDset *ED, uint8_t top, uint8_t bot);

static inline uint8_t getTop(EDset *h)
{
	return (h->code->top);
}

static inline uint8_t getBot(EDset *h)
{
	return (h->code->bot);
}

static inline uint32_t getSegBot(EDset *ED, char c)
{
	uint32_t segBot = 0;
	for (int i = 0; i < c; i++)
	{
		segBot += ED->freq[i];
	}
	return segBot;
}
static inline uint32_t getCharTop(EDset *ED, char c)
{
	return ED->freq[c];
}
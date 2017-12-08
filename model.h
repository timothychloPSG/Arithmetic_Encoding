/*
Romeo Jung 
Timothy Lo

EDset.h
*/

# ifndef _MODEL_H_
# define _MODEL_H_

# include "libfiles.h"
# include "coder.h"

typedef struct Counts Model;

struct Counts 
{
	Coder *range;
	uint32_t *freq;
	uint32_t total;
} ;

Model *newModel();

static inline void delModel(Model *d)
{
	delCoder(d->range);
	free(d->freq);
	free(d);
}

static inline void initFreq(uint32_t *c)
{
	for(int i = 0; i < 256; i++)
	{
		c[i] = 1;
	}
}

void updateRange(Model *ED, uint8_t top, uint8_t bot, char c);

static inline uint8_t getTop(Model *h)
{
	return ((h->range)->top);
}

static inline uint8_t getBot(Model *h)
{
	return ((h->range)->bot);
}

static inline uint32_t getSegBot(Model *ED, char c)
{
	uint32_t segBot = 0;
	for (int i = 0; i < c; i++)
	{
		segBot += ED->freq[i];
	}
	return segBot;
}
static inline uint32_t getCharTop(Model *ED, char c)
{
	return ED->freq[(uint8_t)c];
}

# endif
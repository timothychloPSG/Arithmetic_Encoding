/*
Romeo Jung 
Timothy Lo

EDset.h
*/

# ifndef _MODEL_H_
# define _MODEL_H_

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct counts Model;

struct counts 
{
	coder * code;
	uint32_t * freq;
	uint32_t total;
} ;

static inline void delModel(Model *d)
{
	delCoder(d->code);
	free(d->freq);
	free(d);
}

void updateRange(Model *ED, uint8_t top, uint8_t bot);

static inline uint8_t getTop(Model *h)
{
	return (h->code->top);
}

static inline uint8_t getBot(Model *h)
{
	return (h->code->bot);
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
	return ED->freq[c];
}
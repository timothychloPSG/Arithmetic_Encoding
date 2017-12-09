/*
 * Romeo Jung
 * Timothy Lo
 *
 * 12/7/2017
 *
 * model.h
 *
 * the .h file for model.
 *
 * contains the model struct
 * itself as well as some
 * static inline functions.
 *
 * written by Romeo
 * debugged by Tim
 *
 */

# ifndef _MODEL_H_
# define _MODEL_H_

//** ============= includes ========== **//

# include "libfiles.h"
# include "coder.h"

//** ============ struct declaration ======= **//

typedef struct Counts Model;

struct Counts 
{
	Coder *range;
	uint32_t *freq;			// the frequency table for characters
	uint32_t total;			// the total number of characters on the freq
} ;

//** ========== function headers =========== **//

Model *newModel();
void updateRange( Model *, FILE *, uint16_t, uint16_t, char);

//** ========== static inline functions ====== **//

/**
 * delModel function.
 *
 * deletes the given model.
 *
 * @param d the model to be deleted
 */
static inline void delModel(Model *d)
{
	delCoder(d->range);
	free(d->freq);
	free(d);
}

/**
 * initFreq function.
 *
 * increments the given char table c.
 *
 * @param c the frequency table.
 */
static inline void initFreq(uint32_t *c)
{
	for(int i = 0; i < 256; i++)
	{
		c[i] = 1;
	}
}

/**
 * getTop function.
 * 
 * gets the top from the coder.
 *
 * @param h the model to be looked at
 *
 * @return the frequency 
 *
 */
static inline uint32_t getTop(Model *h)
{
	return ((h->range)->top);
}

/**
 * getBottom function.
 *
 * gets the bottom from the 
 * coder.
 *
 * these functions exist because I 
 * didn't want to access coder directly.
 *
 * @param h the model to be looked at
 *
 * @return the frequency bottom
 *
 */
static inline uint32_t getBot(Model *h)
{
	return ((h->range)->bot);
}


/**
 * getSegBot function.
 *
 * gets the bottom count of the
 * accumulated frequency from adding
 * up all the frequencies of characters before it.
 *
 * @param ED the model to be looked at
 *
 * @param c the char to be counted till
 *
 * @return segBot the accumulated frequency
 */
static inline uint32_t getSegBot(Model *ED, char c)
{
	uint32_t segBot = 0;
	for (int i = 0; i < c; i++)
	{
		segBot += ED->freq[i];
	}
	return segBot;
}

/**
 * getCharCount function.
 *
 * gets the character count in the frequency table.
 *
 * because you can just add this to the result of the
 * top to get the accumulated frequency top for the character.
 *
 * renamed from getCharTop, if errors arise, look for this function.
 *
 * @param ED the model to be looked at
 * 
 * @param c the char to be referenced
 *
 * @return the frequency of the char on the frequency table.
 *
 */
static inline uint32_t getCharCount(Model *ED, char c)
{
	return ED->freq[(uint8_t)c];
}

# endif

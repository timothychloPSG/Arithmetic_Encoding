/*
 * Romeo Jung
 * Timothy Lo
 *
 * 12/7/2017
 *
 * model.h
 *
 * the .h file for model.
 * includes the struct itself
 * and some static inline functions.
 *
 * written by Romeo
 * debugged by Tim
 *
 */

//** ================== includes ================== **//

# include "model.h"
# include "coder.h"

# include "libfiles.h"

/**
 * newModel function.
 *
 * malloc's a model struct and returns
 * the pointer to it.
 *
 * @return m the model malloc'd
 */
Model *newModel()
{
	Model *m = (Model *)(malloc(sizeof(Model)));
	m->range = newCoder();
	m->freq = (uint32_t *)(malloc(sizeof(uint32_t)*256));
	initFreq(m->freq);					//for initializing the freq table to 1's
	m->total = 256;
	return m;

}

/**
 * updateRange function.
 *
 * updates the range with the
 * new top and bottom, then 
 * runs through the updateStatus
 * function inside coder.c.
 * Then increments the frequency table
 * and the total count of the characters.
 *
 * @param top the new top to be set
 * 
 * @param bot the new bottom to be set
 *
 * @param c the character being encoded
 */
void updateRange(Model *ED, uint16_t top, uint16_t bot, char c)
{
	Coder *code = ED->range;
	code->top  = top;
	code->bot  = bot;

	updateStatus(code);

	(ED->freq[(uint8_t)c])++;
	(ED->total)++;
}

/*
Romeo Jung
Timothy Lo

EDset.c
*/

# include "model.h"
# include "coder.h"

# include "libfiles.h"

Model *newModel()
{
	Model *m = (Model *)(malloc(sizeof(Model)));
	m->range = newCoder();
	m->freq = (uint32_t *)(malloc(sizeof(uint32_t)*256));
	initFreq(m->freq);
	m->total = 256;
	return m;

}

void updateRange(Model *ED, uint8_t top, uint8_t bot, char c)
{
	Coder *code = ED->range;
	code->top  = top;
	code->bot  = bot;
	updateStatus(code);
	(ED->freq[(uint8_t)c])++;
	(ED->total)++;
}
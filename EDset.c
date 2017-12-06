/*
Romeo Jung
Timothy Lo

EDset.c
*/

# include "model.h"
# include 


void updateRange(EDset *ED, uint8_t top, uint8_t bot, char c)
{
	coder * code = ED->code;
	code->top  = top;
	code->bot  = bot;
	updateStatus(code);
	(ED->freq[c])++
	(ED->total)++
}
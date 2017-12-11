/**
 * Romeo Jung
 * Timothy Lo
 *
 * 12/7/2017
 *
 * AR.c
 *
 * Where the encoding and the
 * decoding functions are.
 * Depends on the model and coder
 * functions to change the structs
 * respectively to encode and decode.
 *
 * written by Romeo
 * debugged by Tim
 *
 */

/** ===================== Libraries ============== **/

# include "AR.h"
# include "coder.h"
# include "model.h"

# include <stdio.h>
# include <math.h>
# include <stdlib.h>

/**
 * encode function.
 *
 * encodes a given char.
 * expecting a null character
 * at the end of the stream.
 *
 * @param mod the continuing model
 * to encode from the input given
 *
 * @param c the char given to be 
 * encoded next
 *
 */
void encode(Model *mod, FILE *f, char c, uint8_t *outbits, uint8_t *pending)
{
	uint16_t top = getTop(mod);
	uint16_t bot = getBot(mod);
	uint32_t total = mod->total;
	uint32_t segBot = getSegBot(mod, c);
	uint32_t segTop = segBot + getCharCount(mod, c);
	uint16_t newTop = calcRange(top, bot, total, segTop);
	uint16_t newBot = calcRange(top, bot, total, segBot);

	//printf("newtop newbot %d\n %d\n", newTop, newBot);

	updateRange(mod, f, newTop - 1, newBot, c, outbits, pending);
}

/**
 * cleanup function.
 *
 * cleans up after encoding.
 * it encodes a null character,
 * ties up ends, frees the model,
 * then closes the output file given.
 *
 * @param mod the model
 *
 * @param f the file to write out 
 * final values to
 */
void cleanup (Model *mod, FILE *f)
{

	uint8_t outbits = 0;
	uint8_t pending = 0;
	uint8_t prevbit = 0;

	encode(mod, f, '\0', &outbits, &pending);

	uint8_t bit = 0;
	for(int i = 0; i < 16; i++)
	{
		prevbit = bit;
		bit = getBit(BOT, i, (mod->range));
		printf("%u",bit);
		if(i == 1 && pending != 0)
		{
			for(int j = i; j < (i+pending); j++)
			{
				printf("%u", !prevbit);
				chBlock(!prevbit, f, (mod->range));
			}

		}
		chBlock(bit, f, mod->range);
	}

	//uint8_t totalout = 16 - (outbits + pending);

	/*
	for(int i = 0; i < totalout; i++)
	{
		uint8_t bit = getBit(BOT, i, (mod->range));
		chBlock(bit, f, mod->range);
	}*/

	fwrite(&((mod->range)->block), sizeof(uint8_t), 1, f);

	delModel(mod);
	int i = fclose(f);

	if(i == EOF)
	{
		printf("something went wrong");
		exit(1);
	}
}

/**
 * decode function.
 *
 * decodes from the number given.
 * returns by how many spaces we shifted
 * by changing the value inside shift, an
 * int pointer.
 *
 * @param mod the model
 *
 * @param number the number to compare
 * to top and bottom in the model
 *
 * @param shift the int pointer to signify
 * how many bits we're shifting the new
 * number to.
 *
 * @return the decoded char
 *
 */
char decode(Model *m, uint32_t number, uint8_t *outbits, uint8_t *pending)
{

	uint16_t acc = 0;
	uint16_t range = 0;
	uint8_t ch = 0;

	while(number >= range)							// compares all bottoms until one of them's bigger than the number
	{
		acc = getSegBot(m, ch);
		range = calcRange(getTop(m), getBot(m), m->total, acc);
		ch += 1;
	}

	//printf("\n\n\n\n\n\n\n%c\n\n\n\n\n\n\n", ch);
	ch -= 2;


	acc =  getSegBot(m, ch);
	uint16_t newbot = calcRange(getTop(m), getBot(m), m->total, acc);
	acc = acc + (m->freq)[ch];
	uint16_t newtop = calcRange(getTop(m), getBot(m), m->total, acc);

	updateRange(m, NULL, newtop-1, newbot, ch, outbits, pending);

	printf("\n\n\n%d\n\n", m->total);

	return ch;

}


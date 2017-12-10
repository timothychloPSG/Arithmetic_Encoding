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
void encode(Model *mod, FILE *f, char c)
{
	uint16_t top = getTop(mod);
	uint16_t bot = getBot(mod);
	uint32_t total = mod->total;
	uint32_t segBot = getSegBot(mod, c);
	uint32_t segTop = segBot + getCharCount(mod, c);
	uint16_t newTop = calcRange(top, bot, total, segTop);
	uint16_t newBot = calcRange(top, bot, total, segBot);

	// printf("newtop newbot %d\n %d\n", newTop, newBot);

	updateRange(mod, f, newTop - 1, newBot, c);
}

/**
 * cleanup function.
 *
 * cleans up after encoding.
 * it ties up ends, frees the model,
 * then closes the output file given.
 *
 * @param mod the model
 *
 * @param f the file to write out 
 * final values to
 */
void cleanup (Model *mod, FILE *f)
{


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
char decode(Model *m, uint32_t number, int *shift)
{

	(m->range)->top = (m->range)->top;
	number = number;
	*shift = *shift;

	return 'c';

}


/*
 * Romeo Jung
 * Timothy Lo
 *
 * 12/7/2017
 *
 * coder.c
 *
 * contains a 
 * rather long function
 * for updating "status"
 * which is just top and bottom
 * then counting for converging
 * and pending bits.
 *
 * written by Romeo
 * debugged by Tim
 *
 */

# include "coder.h"

/**
 * updateStatus function.
 *
 * takes in the coder struct
 * with the changed top and 
 * bottom, and checks for 
 * converging bits and pending bits.
 *
 * @param code the coder struct
 */
void updateStatus(Coder * code, FILE *f, uint8_t *outbits, uint8_t *pendingbits)
{
	uint16_t newtop = 0;
	uint16_t newbot = 0;
	uint8_t writtenbits = 0;

	(*outbits) = 0;
	(*pendingbits) = 0;

	bool output = true;


	for (int i = 0; i < 16; i++)							// looping through 16 bits only -- the original top and bottom
	{										// so that we don't forever go through the newly added bits

		uint8_t top = getBit(TOP, i, code);					// get the value of the top bit
		uint8_t bot = getBit(BOT, i, code);					// get the value of the bottom bit

		

		//** ======= for converging bits ========== **//
		if(top == bot && output)
		{
			if (bot)							// convergence towards 1
			{
				chBlock(SET, f, code);					// set a bit in the block
				//printf("writing 1\n");
				(*outbits) += 1;
				for (int j = 0; j < (code->pending); j++)		// and for the rest of the pending bits
				{							// (if there are any) clear more bits

					//printf("pending\n");
					chBlock(CLR, f, code);
					(*outbits) += 1;
				}

				code->pending = 0;					// reset counter for pending bits
			}
			else								// convergence towards 0
			{
				chBlock(CLR, f, code);					// clear a bit in the block
				//printf("writing 0\n");
				(*outbits) += 1;
				for (int j = 0; j < (code->pending); j++)		// deal with pending bits
				{
					//printf("pending\n");
					chBlock(SET, f, code);
					(*outbits) += 1;
				}
				code->pending = 0;
			}
		}
		
		//** ========== if bits converge in the middle ====== **//
		else if(top == bot)
		{

			newtop = newtop << 1;
			newbot = newbot << 1;

			if(top)
			{
				newtop |= 1;
				newbot |= 1;
			}

			writtenbits++;
		}

		//** ========== for pending bits ========== **//
		else if( top == 0 && bot == 1 && !output && writtenbits == 1)
		{
			(*pendingbits) += 1;

			code->pending+=1;						// increment the number of pending bits
		}

		//** ========= if the bits differ ========= **//
		else
		{

			output = false;

			newtop = newtop << 1;
			newbot = newbot << 1;

			if(top) //is 1
			{
				newtop |= 1;
			}
			
			if(bot) //is 1
			{
				newbot |= 1;
			}

			writtenbits++;
			
		}

		// for debugging purposes
		// printStatus(code->top, code->bot, writtenbits, newtop, newbot, output, code->pending, top, bot);

	}

	writtenbits = 16 - writtenbits;

	for(int i = 0; i < writtenbits; i++)
	{
		newtop = newtop << 1;
		newbot = newbot << 1;

		newtop |= 1;
	}

	code->top = newtop;
	code->bot = newbot;



}

void printStatus( uint16_t top, uint16_t bot, uint16_t writtenbits, uint16_t newtop, uint16_t newbot, bool outputmode, uint16_t pending, uint8_t topbit, uint8_t botbit)
{
	printf("\n\n\n\ttop bit: %d\n\tbottom bit:%d\n\n\n\nCurrent Top: %d\nCurrent Bottom: %d\nWritten bits: %d\nNew Top: %d\nNew Bottom: %d\nOutput mode: %d\npending: %d\n\n", topbit, botbit, top, bot, writtenbits, newtop, newbot, outputmode, pending);
}



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
void updateStatus(Coder * code)
{
	uint16_t current = 0;								// current cursor on top and bottom -- because we'll be
											// shifting bits for output and we don't want to skip a bit

	for (int i = 0; i < 16; i++)							// looping through 16 bits only -- the original top and bottom
	{										// so that we don't forever go through the newly added bits

		uint8_t top = getBit(TOP, current, code);				// Get the value of the top bit
		uint8_t bot = getBit(BOT, current, code);				// Get the value of the bottom bit


		//** ======= for converging bits ========== **//
		if(top == bot)
		{
			if (bot)							// convergence towards 1
			{
				chBlock(SET, code);					// set a bit in the block
				for (int j = 0; j < (code->pendingBits); j++)		// and for the rest of the pending bits
				{							// (if there are any) clear more bits
					chBlock(CLR, code);
				}

				code->pendingBits = 0;					// reset counter for pending bits
			}
			else								// convergence towards 0
			{
				chBlock(CLR, code);					// clear a bit in the block
				for (int j = 0; j < (code->pendingBits); j++)		// deal with pending bits
				{
					chBlock(SET, code);
				}
				code->pendingBits = 0;
			}
			code->top = code->top << 1;					// shift both by 1, since we don't need to 
			code->bot = code->bot << 1;					// carry the outputted bit anymore
			set(TOP, 15, code);						// set what we just added to 1 in top's case
											// because we want to be adding a 1.
		}

		//** ========== for pending bits ========== **//
		else if( !top && bot )
		{
			code->pendingBits+=1;						// increment the number of pending bits
			set(TOP, current, code);					// since when we backfill it, top will fill
			clr(BOT, current, code);					// with one and bottom with zero, so we just
											// switch the current bits.
			current += 1;							// increment the cursor because we haven't shifted 
											// the number but we don't want to get stuck here
		}

	}
}

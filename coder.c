/*
Romeo Jung 
Timothy Lo

coder.c
*/
# include "coder.h"
# include "libfiles.h"

void updateStatus(Coder * code)
{
	uint16_t current = 0;										// Used for tracking current bit
	for (int i = 0; i < 16; i++)								// Loop through all 16 bits
	{
		printf("Getting top and bottom bit\n");
		uint8_t top = getBit(TOP, current, code);				// Get the value of the top bit
		uint8_t bot = getBit(BOT, current, code);				// Get the value of the bottom bit
		printf("top: %u\n", top);
		printf("bot: %u\n", bot);
		if(top == bot)											// if convergence
		{
			if (bot)											// if the top and bottom bit are both 1
			{
				chBlock(SET, code);								// Set the corresponding bit in the block
				for (int j = 0; j < (code->pendingBits); j++)
				{
					chBlock(CLR, code);
				}
				code->pendingBits = 0;
			}
			else												// if the top and bottom bit are both 0
			{
				chBlock(CLR, code);								// Clear the corresponding bit in the block
				for (int j = 0; j < (code->pendingBits); j++)
				{
					chBlock(SET, code);
				}
				code->pendingBits = 0;
			}
			code->top = code->top << 1;
			code->bot = code->bot << 1;
			set(TOP, 15, code);
		}
		else if(top == 0 && bot == 1) 							// if the top bit doesn't equal the bottom bit
		{
			code->pendingBits+=1;								// Increment the number of pending bits
			set(TOP, current, code);
			clr(BOT, current, code);
			current += 1;
		}

	}
}

/**
 * Romeo Jung 
 * Timothy Lo
 * 
 * coder.c
 *
 * holds the functionalities
 * that has to do with altering
 * coder.
 *
 **/
# include "coder.h"
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h> 

void updateStatus(coder * code)
{
	uint16_t current = 0;
	for (int i = 0; i < 4; i++)
	{
		uint8_t top = getBit(TOP, current, code)
		uint8_t bot = getBit(BOT, current, code)

		if top == bot
		{
			if (bot)
			{
				setBlock(code);
				for (int j = 0; j < code -> pendingBits; j++)
				{
					clrBlock(code);
				}
			}
			else
			{
				clrBlock(code);
				for (int j = 0; j < code->pendingBits; j++)
				{
					setBlock(code);
				}
			}
		}
		else if( !top && bot) 
		{
			code->pendingBits+=1;
			setBit(TOP, current, code)
			clrBit(BOT, current, code)
			current += 1
		}

	}
}

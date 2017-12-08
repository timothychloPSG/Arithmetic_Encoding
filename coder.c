/*
Romeo Jung 
Timothy Lo

coder.c
*/
# include "coder.h"
# include "libfiles.h"

void updateStatus(Coder * code)
{
	uint16_t current = 0;
	for (int i = 0; i < 4; i++)
	{
		uint8_t top = getBit(TOP, current, code);
		uint8_t bot = getBit(BOT, current, code);

		if(top == bot)
		{
			if (bot)
			{
				chBlock(SET, code);
				for (int j = 0; j < code -> pendingBits; j++)
				{
					chBlock(CLR, code);
				}
			}
			else
			{
				chBlock(CLR, code);
				for (int j = 0; j < code->pendingBits; j++)
				{
					chBlock(SET, code);
				}
			}
		}
		else if(!top && bot) 
		{
			code->pendingBits+=1;
			set(TOP, current, code);
			clr(BOT, current, code);
			current += 1;
		}

	}
}

/*
Romeo Jung
Timothy Lo

AR.c
*/

// The following header files are necessary for encoding
# include "AR.h"
# include "coder.h"
# include "EDset.h"

# include <stdio.h>
# include <math.h>
# include <stdlib.h>

static bool in  = false;
static bool out = false;

void encode(EDset * ED, char c)
{
	uint8_t top = getTop(ED);
	uint8_t bot = getBot(ED);
	uint32_t total = ED->total;
	uint32_t segBot = getSegBot(ED, c);
	uint32_t segTop = segTop + getCharTop(ED, c);
	uint8_t newTop = calcRange(top, bot, total, segTop);
	uint8_t newBot = calcRange(top, bot, total, segBot);
	updateRange(ED, newTop - 1, newBot, c);
}

void cleanup (EDset *ED);
{
	
}

int main(int argc, char *argv[])
{
	int fileIn = 0;

	int c;
	while ((c = getopt(argc, argv, "-pvi:o:")) != -1)
	{
		switch (c)
		{
		    case 'i': { inputFile = strdup(optarg); break; }
		    case 'o': { outputFile = strdup(optarg); break; }
		    case 'v': { verbose = true; break; }
		    case 'p': { print = true; break; }
		}
	}
}
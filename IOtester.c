/**
 * Romeo Jung
 * Timothy Lo
 *
 * 12/7/2017
 *
 * IOtester.c
 *
 * written by Tim
 * debugged by Romeo
 * 
 * The next thing that we have to do now is to do the loop thing that Romeo wants us to do on the paper
 * Basically for this loop function thing it will be separated into 3 functions
 *
 * One of the functions will be used for stiching two numbers (chars or 8 bits) together
 * One of the functions will be used for compaing the bits 
 *
 */

# include <math.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>

# include <errno.h>
# include <string.h>
# include <ctype.h>
# include <getopt.h>


uint16_t parse(uint32_t *buffer, uint8_t cursor)
{
	uint16_t charBuffer = (*buffer >> (32 - (cursor + 16))); 	// Isolate the chunk that you want
	*buffer = *buffer >> (cursor + 16);							// Move over the isolated block to the end 
	return charBuffer;
}

uint32_t stitch(uint32_t preEx, uint8_t newBits)
{
	preEx = preEx << 8;			// Shift the block by 8 bits for the next char
	preEx = preEx | newBits;	// Store the 8 bits in the space shifted 
	return preEx;				// Return the block
}

int main(int argc, char* argv[])
{
	char input[1024];
	char output[1024];
	// bool encode = false;
	// bool decode = false;
	int option = 0;
	FILE *inputFile;
	FILE *outputFile;
	// getopt will process the input taken in from the command line by the user
	while ((option = getopt(argc, argv, "edi:o:")) != -1)
	{
		switch(option)
		{
			// Copy the name of the input file 
			case 'i':
			{
				strcpy(input, optarg); 
				break;
			}
			// Copy the name of the output file
			case 'o':
			{
				strcpy(output, optarg); 
				break;
			}
			// if e flag is set, encode the text
			// case 'e':
			// {
			// 	encode = true; 
			// 	break;
			// }
			// // if d flag is set, decode the ciphertext
			// case 'd':
			// {
			// 	decode = true; 
			// 	break;
			// }
			// print to stderr if unknown symbol
			case '?':
			{
				fprintf(stderr, "[ARGUMENT ERROR] Unknown option supplied {-%c}\n\n", optopt);
			}
			default:
			{
				fprintf(stderr, "[UNKNOWN ERROR]\n"); return 2;
			}
		}
	}
	// if (encode == false && decode == false)
	// {
	// 	fprintf(stderr, "[ARGUMENT ERROR] Neither Encode nor Decode flag raised\n");
	// 	exit(1);
	// }
	// if (encode)
	// {
	// 	printf("Encode is true\n");
	// 	//Obviously this will run encode
	// }
	// if (decode)
	// {
	// 	printf("Decode is true\n");
	// 	//Obviously this will run decode
	// }
	
	//-----------------------------------------------------------------------------
	// This part will read in each byte of an input file and store it into a buffer
	//-----------------------------------------------------------------------------
	inputFile = fopen(input, "rb");	
	if (inputFile == NULL)
	{
		fputs ("File error",stderr); exit (1);
	}
	// This part will get the size of the inputFile
	fseek (inputFile , 0 , SEEK_END);
	long lSize = ftell(inputFile);
	rewind (inputFile);

	// Create a bufer the size of the inputFile to store the information read from it
	char *buffer = (char *)malloc(sizeof(char)*lSize);
	if (buffer == NULL)
	{
		fputs ("Memory error",stderr); 
		exit (2);
	}

	// Read the bytes from the inputFile into buffer
	ssize_t result = fread(buffer, 1, lSize, inputFile);
	if (result != lSize) 
	{
		fputs ("Reading error",stderr); 
		exit (3);
	}
	//-----------------------------------------------------------------------------

	if (encode)
	{
		Model *encodeModel = newModel();
		
	}
	//-----------------------------------------------------------------------------
	// This next part will run the function that Romeo wants me to do (see whiteboard photo)
	//-----------------------------------------------------------------------------
	char buffering[lSize];
	memcpy(buffering, buffer, lSize);
	// AS LONG AS YOU DONT GET PAST LSIZE + 1, YOU WONT HIT THE NULL TERMINATOR 
	uint32_t tracker = 0;
	uint8_t i = 0;
	while (i < 4)
	{
		tracker = stitch(tracker, buffering[i]);	// Stitch together the first 4 chars in tracker
		i++;
	}
	uint8_t replacement = buffering[i];			// Replacement should be equal to the 5th element in the buffer now
	printf("%u\n", replacement);
	uint16_t cursor = 0;
	uint16_t charBuffer = parse(&tracker, cursor);
	printf("charBuffer: %u\n", charBuffer);
	printf("tracker: %u\n", tracker);

	for(int j = 0; j < lSize; j++)
	{
		uint16_t charBuffer = parse(tracker, cursor);
		char something = decode(charBuffer);//other parameters)
		cursor++;
		if (cursor == 8)
		{
			cursor-=8;
			tracker = stitch(tracker, replacement);
			if (buffering[i+1] == 0)
			{
				replacement = 0;
			}
			else
			{
				replacement = buffering[i+1];
			}
			i++;
		}
	
		// Parse the first 16 bits of the buffer
		// char something = put the 16 bits through the decode function
		// if cursor = 8
			// then stitch the next character onto the buffer
			// subtract 8 from cursor
			// if buffering[i+1] == 0
				// replacement = 0
			// replacement = buffering[i+1]
		// increment cursor by 1
	}

	//-----------------------------------------------------------------------------
	// This part will write the things in the buffer to the output file
	//-----------------------------------------------------------------------------
	outputFile = fopen(output, "wb");
	if (outputFile == NULL)
	{
		fputs("File Error",stderr);
		exit (1);
	}
	fwrite(buffer, sizeof(char), lSize, outputFile);
	//-----------------------------------------------------------------------------


	fclose(outputFile);
	fclose(inputFile);
	free(buffer);
	return 0;
}

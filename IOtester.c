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

# include "model.h"
# include "coder.h"
# include "libfiles.h"
# include "AR.h"
# include "IOtester.h"

int main(int argc, char* argv[])
{
	char input[1024];
	char output[1024];
	bool encoding = false;
	bool decoding = false;
	int option = 0;
	FILE *inputFile;
	FILE *outputFile;
	// getopt processes command line input
	while ((option = getopt(argc, argv, "edi:o:")) != -1)
	{
		switch(option)
		{
			// Copy the name of the input file 
			case 'i':
			{
				strcpy(input, optarg); break;
			}
			// Copy the name of the output file
			case 'o':
			{
				strcpy(output, optarg); break;
			}
			//if e flag is set, encode the text
			case 'e':
			{
				encoding = true; break;
			}
			// if d flag is set, decode the ciphertext
			case 'd':
			{
				decoding = true; break;
			}
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
	char buffering[lSize];
	memcpy(buffering, buffer, lSize);
	//-----------------------------------------------------------------------------
	// Open the output file 
	//-----------------------------------------------------------------------------	
	outputFile = fopen(output, "wb");
	if (outputFile == NULL)
	{
		fputs("File Error",stderr);
		exit (1);
	}
	//-----------------------------------------------------------------------------
	// Encode if flag is raised
	//-----------------------------------------------------------------------------
	if (encoding)
	{	
		uint8_t outbits = 0;
		uint8_t pending = 0;
		Model *encodeModel = newModel();
		for(int i = 0; i < lSize; i++)
		{
			encode(encodeModel, outputFile, buffering[i], &outbits, &pending);
		}
		cleanup(encodeModel, outputFile);
	}
	//-----------------------------------------------------------------------------
	// This next part will run the function that Romeo wants me to do (see whiteboard photo)
	//-----------------------------------------------------------------------------
	if (decoding )
	{
		Model *decodingModel = newModel();
		uint32_t tracker = 0;
		uint8_t i = 0;
		while (i < 4)
		{
			tracker = stitch(tracker, buffering[i]);	// Stitch together the first 4 chars in tracker
			i++;
		}
		uint8_t replacement = buffering[i]
		uint16_t cursor = 0;
		for(int j = 5; j < lSize; j++)
		{
			uint8_t outbits = 0;
			uint8_t pending = 0;
			uint16_t charBuffer = parse(tracker, cursor);
			if (pending > 0) 	// Pending bits present from previous decode
			{
				uint16_t buffer = 0;
				for(int x = 1; x < 16; i++)
				{
					if(pending < x)
					{
						bit = (charBuffer >> (15 - i) & 1);
					}
				}
				//write the first character 
			} 
			char decodedChar = decode(decodingModel, charBuffer, &outbits, &pending);
			fwrite(&decodedChar, sizeof(char), 1, outputFile);
			// write decodedChar to the character
			cursor+=outbits;
			if (cursor >= 8)
			{
				cursor-=8;
				tracker = stitch(tracker, replacement);
				if(buffering[i+1] == 0)
				{
					replacement = 0;
				}
				else
				{
					replacement = buffering[i+1];
				}
				i++;
			}
	}

	fclose(inputFile);
	free(buffer);
	return 0;
}

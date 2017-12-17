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

	inputFile = fopen(input, "rb");	
	if (inputFile == NULL)
	{
		fputs ("File error",stderr); exit (1);
	}

	fseek (inputFile , 0 , SEEK_END);
	long lSize = ftell(inputFile);
	rewind (inputFile);


	char *buffer = (char *)malloc(sizeof(char)*lSize);
	if (buffer == NULL)
	{
		fputs ("Memory error",stderr); 
		exit (2);
	}


	ssize_t result = fread(buffer, 1, lSize, inputFile);
	if (result != lSize) 
	{
		fputs ("Reading error",stderr); 
		exit (3);
	}
	char buffering[lSize];
	memcpy(buffering, buffer, lSize);

	outputFile = fopen(output, "wb");
	if (outputFile == NULL)
	{
		fputs("File Error",stderr);
		exit (1);
	}
	//-----------------------------------------------------------------------------
	// Encode 
	//-----------------------------------------------------------------------------
	if (encoding)
	{	
		uint8_t outbits = 0;
		uint8_t pending = 0;
		Model *encodeModel = newModel();
		for(int i = 0; i < lSize; i++)
		{
			printf("\n\n\t\t\t %dth \n\n", i);
			printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n\t\tbuffering : %d\n\n", (encodeModel->range)->top, (encodeModel->range)->bot, buffering[i]); 
			encode(encodeModel, outputFile, buffering[i], &outbits, &pending);
		}
		cleanup(encodeModel, outputFile);
	}

	//-----------------------------------------------------------------------------
	// Decode
	//-----------------------------------------------------------------------------

	if (decoding)
	{
		Model *decodingModel = newModel();

		uint32_t tracker = 0;
		uint8_t i = 0;

		while (i < 4)
		{
			tracker = stitch(tracker, buffering[i]);	// Stitch together the first 4 chars in tracker
			i++;
		}
		//printf("first tracker: %u\n", tracker);
		//
		uint8_t replacement = buffering[i];
		
		//printf("first replacement: %u\n", replacement); 
		
		uint16_t cursor = 0;
		uint8_t outbits = 0;
		uint8_t pending = 0;
		uint16_t charBuffer = 0;
		uint32_t counter = 0;
		uint8_t cursor2 = 0;

		while(true)
		{
			charBuffer = parse(tracker, cursor);

			//printf("\n\n%u\n\n", charBuffer);
			
			printf("%d\n\n", pending);

			printf("\n\n\t\tprev buffer : %d\n\n", charBuffer);


			printf("\n\n\t\t\t\t\tcursor: %u\n\n\t\t\t\ttracker: %u\n\n", cursor, tracker);

			if (pending != 0) 	// Pending bits present from previous decode
			{
				uint16_t buffer = 0;
				uint8_t bit = get(charBuffer, 0); 

				cursor2 = cursor + pending + 1;		// starting position

				buffer = parse(tracker, cursor2);
				buffer = buffer >> 1;
				//printf("cursor : %u, cursor2 : %u", cursor, cursor2);

				if(bit)
				{
					setBit(&buffer, 0);
				}
				charBuffer = buffer;


			}

			printf("\n\n\t\t\t %dth \n\n", counter);
			counter++;
			printf("\n\n\t\tnew buffer : %d\n\n", charBuffer);

			char decodedChar = decode(decodingModel, charBuffer, &outbits, &pending);

			if(decodedChar == '\0')
			{
				break;
			}
			//printf("%c", decodedChar);
			fwrite(&decodedChar, sizeof(char), 1, outputFile);

			//printf("\n\noutbits : %d\n\n", outbits);
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
				//printf("new replacement: %u\n", replacement);
				i++;
			}

		}
	
	
	}

	fclose(inputFile);
	free(buffer);
	return 0;
}

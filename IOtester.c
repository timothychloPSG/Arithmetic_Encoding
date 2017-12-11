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
	// Encode if flag is raised
	//-----------------------------------------------------------------------------
	if (encoding)
	{	
		uint8_t outbits = 0;
		uint8_t pending = 0;
		Model *encodeModel = newModel();
		for(int i = 0; i < lSize; i++)
		{
			//printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n\t\tbuffering : %d\n\n", (encodeModel->range)->top, (encodeModel->range)->bot, buffering[i]); 
			encode(encodeModel, outputFile, buffering[i], &outbits, &pending);
		}
		cleanup(encodeModel, outputFile);
	}

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
		uint8_t replacement = buffering[i];
		//printf("first replacement: %u\n", replacement); 
		uint16_t cursor = 0;
		uint8_t outbits = 0;
		uint8_t pending = 0;
		uint16_t charBuffer = 0;

		while(true)//for(int j = 5; j < lSize; j++)
		{
			charBuffer = parse(tracker, cursor);

			printf("\n\n%u\n\n", charBuffer);

			/**
			if(j == 7)
			{
				break;
			}*/

			if (pending != 0) 	// Pending bits present from previous decode
			{
				uint16_t buffer = 0;
				uint8_t bit = get(charBuffer, 0); //write the first character 
				if (bit)
				{
					setBit(&buffer, 0);
				}
				uint8_t cursor2 = 1;

				for(uint8_t x = 1; x < 16; x++)
				{
					if(pending < x)
					{
						bit = get(charBuffer, x);
						if (bit)
						{
							setBit(&buffer, cursor2);
						}
						cursor2++;
					}
				}		
					

				for(uint8_t x = (cursor + 16); x < (cursor + 16 + pending); x++)
				{
					bit = get32(tracker, x);
					// printf("Bit %u\n", bit);
					if(bit)
					{
						setBit(&buffer, cursor2);
					}
					cursor2++;
				}	
				charBuffer = buffer;


			}

			printf("\n\n\t\tnew buffer : %d\n\n", charBuffer);

			/*
			if(j == 8)
			{
				break;
			}*/

			char decodedChar = decode(decodingModel, charBuffer, &outbits, &pending);

			if(decodedChar == '\0')
			{
				break;
			}
			printf("%c", decodedChar);
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

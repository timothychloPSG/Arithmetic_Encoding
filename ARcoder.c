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
		bool throw = false; 
		Model *encodeModel = newModel();
		for(int i = 0; i < lSize; i++)
		{
			if(DEBUG_0)
			{
				printf("\n\n\t\t\t %dth \n\n", i);
				printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n\t\tbuffering : %d\n\n", (encodeModel->range)->top, (encodeModel->range)->bot, buffering[i]); 
			}
			encode(encodeModel, outputFile, buffering[i], &outbits, &pending, &throw);
		}
		cleanup(encodeModel, outputFile);
	}

	//-----------------------------------------------------------------------------
	// Decode
	//-----------------------------------------------------------------------------

	if (decoding)
	{
		/**
		Model *decodingModel = newModel();

		*/
		uint32_t tracker = 0;
		uint32_t rpc = 0;
		uint8_t i = 0;
		uint8_t replacement;
		//bool printed = false;

		
		while (i < 4)
		{
			tracker = stitch(tracker, buffering[i]);	// Stitch together the first 4 chars in tracker
			i++;
		}

		printf("%u\n\n", tracker);

		
										if(DEBUG_0)
										{
											printf("\n\n\t\t\t\t\tfirst tracker: %u to %u\n", rpc, rpc+4);
										}
	
		replacement = buffering[i];
		
										if(DEBUG_0)
										{
											printf("first replacement: %u\n", replacement); 
										}

		/**
		uint16_t cursor = 0;
		uint8_t outbits = 0;
		uint8_t pending = 0;
		uint16_t charBuffer = 0;
		uint32_t counter = 0;
		uint8_t cursor2 = 0;
		
		bool stitched = true;
		*/

		for(int a = i; a < lSize; a++)//while(true)
		{
					replacement = buffering[a];
					/**
					if(stitched)
					{
						stitched = false;
						printf("%u ", replacement);

					}*/
					printf("%u ", replacement);
					//tracker = stitch(tracker, replacement);
					//printf("%u\n", tracker);
			
			/**

			charBuffer = parse(tracker, cursor);

			
										if(DEBUG_0)
										{
			
											printf("%d\n\n", pending);

											printf("\n\n\t\tprev buffer : %d\n\n", charBuffer);


											printf("\n\n\t\t\t\t\tcursor: %u\n\n\t\t\t\ttracker: %u\n\n", cursor, tracker);
											printf("\n\n\t\t\t\t\ttracker num: %u to %u", rpc, rpc+4);
										}


			if (pending != 0) 	// Pending bits present from previous decode
			{
				uint16_t buffer = 0;
				uint8_t bit = get(charBuffer, 0); 

				cursor2 = cursor + pending + 1;		// starting position

				buffer = parse(tracker, cursor2);
				buffer = buffer >> 1;

				if(bit)
				{
					setBit(&buffer, 0);
				}
				charBuffer = buffer;
			}

										if(DEBUG_0)
										{		

											printf("\n\n\t\t\t %dth \n\n", counter);
											printf("\n\n\t\tnew buffer : %d\n\n", charBuffer);
										}

			counter++;

			char decodedChar = decode(decodingModel, charBuffer, &outbits, &pending, &printed);

			if(DEBUG_0)
			{
				printf("\n%c\n", decodedChar);
			}
			if(decodedChar == '\0')
			{
				printf("sss");
				break;
			}

			else if(decodedChar == -1)
			{
				printf("we've reached an error.\n");
				exit(0);
			}


			fwrite(&decodedChar, sizeof(char), 1, outputFile);

			cursor+=outbits;



			if (printed)//cursor >= 8)
			{
				stitched = true;
				printed = false;
				rpc += 1;
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
			}*/

		}
	
	
	}

	fclose(inputFile);
	free(buffer);
	return 0;
}

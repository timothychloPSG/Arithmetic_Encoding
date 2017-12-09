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
 */


# include "libfiles.h"

int main(int argc, char* argv[])
{
	char *input = NULL;
	char *output = NULL;
	bool encode = false;
	bool decode = false;
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
				input = strdup(optarg); 
				break;
			}
			// Copy the name of the output file
			case 'o':
			{
				output = strdup(optarg); 
				break;
			}
			// if e flag is set, encode the text
			case 'e':
			{
				encode = true; 
				break;
			}
			// if d flag is set, decode the ciphertext
			case 'd':
			{
				decode = true; 
				break;
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
	if (encode == false && decode == false)
	{
		fprintf(stderr, "[ARGUMENT ERROR] Neither Encode nor Decode flag raised\n");
		exit(1);
	}
	if (encode)
	{
		printf("Encode is true\n");
		//Obviously this will run encode
	}
	if (decode)
	{
		printf("Decode is true\n");
		//Obviously this will run decode
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
	printf("The size of the file is %lu\n", lSize);
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

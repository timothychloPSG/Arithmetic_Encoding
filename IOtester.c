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

int main(int argc, char* argv[])
{
	char *input = NULL;
	char *output = NULL;
	bool encode = false;
	bool decode = false;
	int option = 0;
	FILE *inputFile;
	//FILE *outputFile;

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
	// This part is kinda just bullshit for now
	if (output)
	{
		printf("There is some input for output");
	}
	if (encode && decode)
	{
		printf("Encode and Decode are both true");
	}
	
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

	fclose(inputFile);
	free(buffer);
	return 0;
}

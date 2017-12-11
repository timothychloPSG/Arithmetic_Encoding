/**
 * test file modified by Romeo 
 */

# include "libfiles.h"
# include "coder.h"
# include "model.h"
# include "AR.h"

# include "IOtester.h"

int main(void)
{

	/**
	 *
	//encode things
	Model *m = newModel();

	printf("%d\n", (m->range)->top);
	printf("%d\n", (m->range)->bot);

	FILE *output = fopen("out.txt", "w+"); 

	uint8_t pending = 0;
	uint8_t outbits = 0;

	printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n", (m->range)->top, (m->range)->bot);
	printf("\n\n\n================================ b =====================\n\n\n");
	encode(m, output, 'b', (&outbits), (&pending));

	printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n", (m->range)->top, (m->range)->bot); 
	printf("\n\n\n================================ a =====================\n\n\n");
	encode(m, output, 'a', (&outbits), (&pending));

	printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n", (m->range)->top, (m->range)->bot);
	printf("\n\n\n================================ g =====================\n\n\n");
	encode(m, output, 'g', (&outbits), (&pending));

	printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n", (m->range)->top, (m->range)->bot);
	        printf("\n\n\n================================ d =====================\n\n\n");
		        encode(m, output, 'd', (&outbits), (&pending));

	printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n", (m->range)->top, (m->range)->bot);
	        printf("\n\n\n================================ c =====================\n\n\n");
		        encode(m, output, 'c', (&outbits), (&pending));

	printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n", (m->range)->top, (m->range)->bot);
	        printf("\n\n\n================================ d =====================\n\n\n");
		        encode(m, output, 'd', (&outbits), (&pending));

	printf("\n\n\t\ttop: %d\n\n\t\tbot: %d\n\n", (m->range)->top, (m->range)->bot);
	        printf("\n\n\n================================ b =====================\n\n\n");
		        encode(m, output, 'b', (&outbits), (&pending));

	printf("DONE ==================================================== \n\n\n\n\n");

	printf("coder total : %d\n", (m->total));
	printf("coder top: %d\ncoder bot: %d\n\n", (m->range)->top, (m->range)->bot);
	printf("coder pending: %d\n\n", (m->range)->pending);
	printf("coder block: %d\n\n", (m->range)->block);

	int counter = 0;
	int total = 0;

	for(int i = 0 ; i < 256; i++)
	{
		if(i % 10 == 0)
		{
			printf("count: %d\t total: %d\t", counter, total);
			counter = 0;
		}
		if(i % 5 == 0)
		{
			printf("\n");
		}
		counter += (m->freq)[i];
		total += (m->freq)[i];
		printf("[%c : %d]\t", i, (m->freq)[i]); 
	}
	

	cleanup(m, output); 
	*/

	Model *m = newModel();
	uint32_t number = 0;

	number = stitch(number, 'a');
	number = stitch(number, 'b');
	number = stitch(number, 'c');
	number = stitch(number, 'd');

	uint16_t compare = parse(number, 0);

	uint8_t outbits = 0;
	uint8_t pending = 0;

	for(int i = 0; i < 
	uint8_t ch = decode(m, number, &outbits, &pending);

	printf("%c\n", ch);
	printf("%d\n%d\n", outbits, pending);



	/*
	uint32_t preEx = 0;

	preEx = stitch(preEx, 'a');

	printf("preEx now : %d\n", preEx);

	preEx = stitch(preEx, 'b');

	printf("preEx now : %d\n", preEx);

	preEx = stitch(preEx, 'c');

	printf("preEx now : %d\n", preEx);

	preEx = stitch(preEx, 'd');

	printf("preEx now : %d\n", preEx);

	uint16_t parsed = parse(preEx, 0); 

	printf("parsed : %d\n", parsed);

	preEx = stitch(preEx, 'e');

	printf("preEx now: %d\n", preEx);

	parsed = parse(preEx, 12);

	printf("parsed : %d\n", parsed);

	*/
	return 0;
}

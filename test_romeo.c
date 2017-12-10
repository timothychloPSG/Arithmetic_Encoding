/**
 * test file modified by Romeo 
 */

# include "libfiles.h"
# include "coder.h"
# include "model.h"
# include "AR.h"

int main(void)
{

	/**
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
	uint16_t number = 24832;
	(m->freq)['b'] += 1;
	(m->total) += 1;
	uint8_t outbits = 0;
	uint8_t pending = 0;


	uint8_t ch = decode(m, number, &outbits, &pending);

	printf("%c\n", ch);
	printf("%d\n%d\n", outbits, pending);

	return 0;
}

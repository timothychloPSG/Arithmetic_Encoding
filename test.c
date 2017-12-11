# include "libfiles.h"
# include "model.h"
# include "coder.h"
# include "AR.h"
# include "IOtester.h"


int main(void)
{

	uint32_t charBuffer = 325346560;
	uint16_t number = 13894;
	uint8_t pending = 2; 
	uint8_t cursor = 4;

	if (pending > 0) 	// Pending bits present from previous decode
	{
		uint16_t buffer = 0;
		uint8_t bit = get(number, 0); //write the first character 
		if (bit)
		{
			setBit(&buffer, 0);
		}
		uint8_t cursor2 = 1;


		for(int x = 1; x < 16; x++)
		{
			if(pending < x)
			{
				bit = get(number, x);
				if (bit)
				{
					setBit(&buffer, cursor2);
				}
				cursor2++;
			}
		}
		printf("Buffer: %u\n Cursor2: %d\n", buffer, (cursor2));		
		
		for(int x = (cursor + 16); x < (cursor + 16 + pending); x++)
		{
			bit = get32(charBuffer, x);
			printf("Bit %u\n", bit);
			if(bit)
			{
				setBit(&buffer, cursor2);
			}
			cursor2++;
		}
		printf("Buffer: %u\n", buffer);		
	} 
	return 0;
}



# include "libfiles.h"
# include "coder.h"
# include "model.h"

int main(void)
{
	printf("Creating a new code\n");
	Coder *code = newCoder();
	Model *model = newModel();
	
	// Sets the top to 1111

	code->top = 65535;
	code->bot = 0;

	set(BOT,0,code);

	printf("%d", code->bot);


	// Sets the bot to 1100 0000 0000 0000
	
	printf("Beginning to updateStatus\n");

	updateStatus(code);

	printf("Now printing out the results of updateStatus\n");
	printf("Top: %u\n", code->top);
	printf("Bot: %u\n",code->bot);
	printf("Block: %u\n",code->block);
	delCoder(code);
	delModel(model);
	return 0;
}


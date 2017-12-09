/**
 * test file modified by Romeo 
 */

# include "libfiles.h"
# include "coder.h"
# include "model.h"

int main(void)
{
	Model *m = newModel();

	(m->range)->top = MAXTOP;
	(m->range)->bot = 0;

	for(int i = 0; i < 4; i++)
	{
		set(BOT, i, (m->range));
	}

	printf("%d", (m->range)->bot);

	
	delModel(m);
	return 0;
}

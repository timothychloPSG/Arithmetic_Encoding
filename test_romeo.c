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

	set(BOT, 5, m->range);
	clr(TOP, 5, m->range);
	clr(TOP, 6, m->range);
	

	for(int i = 8; i < 16; i++)
	{
		clr(TOP, i, m->range);
	}

	printf("%d\n", (m->range)->top);
	printf("%d\n", (m->range)->bot);

	updateRange(m, NULL, (m->range)->top, (m->range)->bot, 'c');

	printf("\n\nafter changing: top: %d\nbot: %d\n", (m->range)->top, (m->range)->bot);
	printf("block: %d\npending: %d\nspace: %d\n", (m->range)->block, (m->range)->pending, (m->range)->space);

	delModel(m);
	return 0;
}

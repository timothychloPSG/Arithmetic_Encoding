/**
 * test file modified by Romeo 
 */

# include "libfiles.h"
# include "coder.h"
# include "model.h"
# include "AR.h"

int main(void)
{
	Model *m = newModel();

	printf("%d\n", (m->range)->top);
	printf("%d\n", (m->range)->bot);

	encode(m, NULL, 'a');

	//updateRange(m, NULL, (m->range)->top, (m->range)->bot, 'c');

	printf("\n\nafter changing: top: %d\nbot: %d\n", (m->range)->top, (m->range)->bot);
	printf("block: %d\npending: %d\nspace: %d\n", (m->range)->block, (m->range)->pending, (m->range)->space);

	delModel(m);
	return 0;
}

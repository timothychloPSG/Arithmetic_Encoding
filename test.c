# include "libfiles.h"
# include "coder.h"
# include "model.h"

int main()
{
	Coder *code = newCoder();
	Model *model = newModel();
	delCoder(code);
	delModel(model);
	return 0;
}

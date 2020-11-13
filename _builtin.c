#include "hsh.h"









int _isbuiltin(char *comm)
{
	unsigned int i;
	char *builtlist[] = {"exit", "env", "setenv", "unsetenv", "cd",
			     "alias", "help", "history", NULL};

	i = 0;
	while (builtlist[i])
	{
		if (_strcmp(comm, builtlist[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}







int _exec_builtin()
{
	printf("This is a builtin\n");
	return (0);
}

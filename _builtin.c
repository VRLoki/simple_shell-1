#include "hsh.h"

int	_isbuiltin(char *comm)
{
	unsigned int	i;
	char		*builtlist[] = {"exit", "env", "setenv",
		"unsetenv", "cd", "alias", "help", "history", NULL};
	i = 0;
	while (builtlist[i])
	{
		if (_strcmp(comm, builtlist[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}



int	_get_builtin_fct(char **comm, param_t *param)
{
	if (_strcmp(comm[0], "exit") == 0)
		return (_ft_exit(comm[1], param));
	else
		printf("not done yet\n");
	return (1);
}

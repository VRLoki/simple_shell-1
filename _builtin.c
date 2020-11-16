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



int	_get_builtin_fct(int built_nbr, char **comm, int count, char **env)
{
	if (built_nbr == 1)
		return (_ft_exit(comm[1], count, env));
	else
		printf("not done yet\n");
}

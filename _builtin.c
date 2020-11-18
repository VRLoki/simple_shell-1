#include "hsh.h"

/**
 * _isbuiltin - check if the command is a builtin function.
 *
 * @comm: the command to check.
 *
 * Return: the number of the command or 0
 */

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

/**
 * _get_builtin_fct - call the right builtin function.
 *
 * @comm: the command to excute.
 *
 * Return: the exit number of the command or 1
 */

int	_get_builtin_fct(char **comm, param_t *param)
{
	if (_strcmp(comm[0], "exit") == 0)
		return (_ft_exit(comm[1], param));
	if (_strcmp(comm[0], "env") == 0)
		return (_ft_env(param));
	if (_strcmp(comm[0], "setenv") == 0)
		return (_ft_setenv(comm[1], comm[2], comm[3] == NULL ? 0 : atoi(comm[3]), param));
	if (_strcmp(comm[0], "unsetenv") == 0)
		return (_ft_unsetenv(comm[1], param));
	if (_strcmp(comm[0], "alias") == 0)
		return (_ft_alias(comm, param));


	printf("not done yet\n");
	return (1);
}

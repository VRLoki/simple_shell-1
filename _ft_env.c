#include "hsh.h"

/**
 * _ft_env - display all environnements variables of the shell.
 *
 */

int	_ft_env(param_t *param)
{
	char		**envfull;
	unsigned int	i;

	envfull =_getEnvChar(param->envlist);
	if (envfull != NULL)
	{
		i = 0;
		while (envfull[i] != NULL)
		{
			_puts(envfull[i]);
			_putchar('\n');
			free(envfull[i]);
			i++;
		}
		free(envfull);
		return (0);
	}
	return (-1);
}

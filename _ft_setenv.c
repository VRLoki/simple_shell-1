#include "hsh.h"

/**
 * _ft_setenv - initialize a new environment variable, or modify an existing one.
 *
 * @name: the name of the environnement.
 * @value: the value.
 * @overwrite: authorize to replace a value if the name already exist.
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail -1
 */

int	_ft_setenv(char *name, char *value, int overwrite, param_t *param)
{
	char	**envfull;
	envl_t	*comp;
	envl_t	*pre_node;

	comp = (envl_t *)malloc(sizeof(envl_t));
	if (comp == NULL || param->envlist == NULL)
	{
		return (-1);
	}
	comp = param->envlist;
	while (comp != NULL)
	{
		if (_strcmp(name, comp->var) == 0)
		{
			if (overwrite != 0)
			{
				free(comp->value);
				comp->value = _strdup(value);
			}
			return (0);
		}
		if (comp->next == NULL)
		{
			pre_node = comp;
		}
		comp = comp->next;
	}
	if (comp == NULL)
	{
		comp = (envl_t *)malloc(sizeof(envl_t));
		if (comp == NULL)
			return (-1);
		comp->var = _strdup(name);
		comp->value = _strdup(value);
		comp->next = NULL;
		pre_node->next = comp;
	}
	return (0);
}

#include "hsh.h"

/**
 * _ft_unsetenv - remove an environment variable.
 *
 * @name: the name of the variable.
 * @param: global parameters of the shell.
 *
 * Return: 0 (Sucess) or -1 if fail.
 */

int	_ft_unsetenv(char *name, param_t *param)
{
	envl_t	*pre_node;
	envl_t	*del_node;

	del_node = (envl_t *)malloc(sizeof(envl_t));
	pre_node = (envl_t *)malloc(sizeof(envl_t));
	if (del_node == NULL || pre_node == NULL)
	{
		return (-1);
	}
	del_node = param->envlist;
	pre_node = param->envlist;
	if (_strcmp(name, del_node->var) == 0)
	{
		param->envlist = param->envlist->next;
		free(del_node->var);
		free(del_node->value);
		return (0);
	}
	while (del_node != NULL)
	{
		del_node = del_node->next;
		if (_strcmp(name, del_node->var) == 0)
		{
			pre_node->next = del_node->next;
			free(del_node->var);
			free(del_node->value);
			return (0);
		}
		pre_node = pre_node->next;
	}
	return (0);
}

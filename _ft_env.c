#include "hsh.h"

/**
 * _error_env - display the error message of the function exit.
 *
 * @command: the exit number who make the error.
 * @param: global parameters of the shell.
 *
 * Return: 2 always
 */

int     _error_env(char *command, param_t *param)
{
	char *dispmess, *conv;
	int count = param->count;

	conv = _convert_base(count, 10, 0);
	dispmess = _strdup(param->bashname);
	dispmess = _str_concat_f(dispmess, ": ");
	dispmess = _str_concat_f(dispmess, conv);
	dispmess = _str_concat_f(dispmess, ": ");
	dispmess = _str_concat_f(dispmess, command);
	dispmess = _str_concat_f(dispmess, ": ");
	dispmess = _str_concat_f(dispmess, "Error syntax: [VARIABLE] [VALUE]");
	dispmess = _str_concat_f(dispmess, "\n");
	free(conv);
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	return (2);
}

/**
 * _ft_env - display all environnements variables of the shell.
 *
 * @param: global parameter variable
 *
 * Return: 0 on success, -1 if failure
 */

int	_ft_env(param_t *param)
{
	char		**envfull;
	unsigned int	i;

	envfull = _getEnvChar(param->envlist);
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


/**
 * _ft_setenv - initialize a new environment variable,
 * or modify an existing one.
 *
 * @comm: command line
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail -1
 */

int	_ft_setenv(char **comm, param_t *param)
{
	envl_t  *comp;
	envl_t  *pre_node;

	if (comm == NULL || param->envlist == NULL)
		return (-1);
	if (comm[1] == NULL || comm[2] == NULL)
	{
		_error_env(comm[0], param);
		return (-1);
	}

	comp = param->envlist;
	while (comp != NULL)
	{
		if (_strcmp(comm[1], comp->var) == 0)
		{
			free(comp->value);
			comp->value = _strdup(comm[2]);
			return (0);
		}
		if (comp->next == NULL)
			pre_node = comp;
		comp = comp->next;
	}
	if (comp == NULL)
	{
		comp = (envl_t *)malloc(sizeof(envl_t));
		if (comp == NULL)
			return (-1);
		comp->var = _strdup(comm[1]);
		comp->value = _strdup(comm[2]);
		comp->next = NULL;
		pre_node->next = comp;
	}
	return (0);
}


/**
 * _ft_unsetenv - remove an environment variable.
 *
 * @comm: command line
 * @param: global parameters of the shell.
 *
 * Return: 0 (Sucess) or -1 if fail.
 */

int	_ft_unsetenv(char **comm, param_t *param)
{
	envl_t  *pre_node;
	envl_t  *del_node;

	if (comm == NULL)
		return (-1);
	if (comm[1] == NULL)
		_error_env(comm[0], param);
		return (-1);
	del_node = param->envlist;
	pre_node = param->envlist;
	if (_strcmp(comm[1], del_node->var) == 0)
	{
		param->envlist = param->envlist->next;
		free(del_node->var);
		free(del_node->value);
		free(del_node);
		return (0);
	}
	while (del_node != NULL)
	{
		if (_strcmp(comm[1], del_node->var) == 0)
		{
			pre_node->next = del_node->next;
			free(del_node->var);
			free(del_node->value);
			free(del_node);
			return (0);
		}
		pre_node = del_node;
		del_node = del_node->next;
	}

	return (0);
}

#include "hsh.h"

/**
 * _ft_alias - handle the alias built_in
 *
 * @comm: command entered by the user
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_ft_alias(char **comm, param_t *param)
{
	int i = 1;
	int ret = 0;
	int err = 0;

	if (comm[1] == NULL)
	{
		_print_all_alias(param);
		return (0);
	}

	while (comm[i])
	{
		if(_str_findeq(comm[i]))
		{
			_assign_alias(comm[i], param);
		}
		else
			err = _print_single_alias(comm[i], param);

		if (err == 1)
			ret = 1;
		i++;
	}

	return (ret);
}


/**
 * _print_all_alias - prints all the alias
 *
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_print_all_alias(param_t *param)
{
	aliasl_t *node;

	node = param->alias;
	while (node)
	{
		_print_single_alias(node->var, param);
		node = node->next;
	}

	return (0);
}





/**
 * _print_single_alias - prints all the alias
 *
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_print_single_alias(char *name, param_t *param)
{
	aliasl_t *node;
	char *line;

	node = param->alias;
	while (node)
	{
		if (_strcmp(node->var, name) == 0)
		{
			line = _strdup(name);
			line = _str_concat(line,"='");
			line = _str_concat(line, node->value);
			line = _str_concat(line,"'\n");
			write(STDOUT_FILENO, line, _strlen(line));
			free(line);
			return (0);
		}
		node = node->next;
	}

	line = _strdup("alias: ");
	line = _str_concat(line, name);
	line = _str_concat(line, " not found\n");
	write(STDERR_FILENO, line, _strlen(line));
	free(line);
	return (1);

}





/**
 * _str_findeq - determine if string is an assignement
 *
 * @param: global parameters of the shell.
 *
 * Return: postion of the '=' if assignement,
 * else 0
 */

int	_str_findeq(char *str)
{
	int i;

	if (_strlen(str) <= 1)
		return (0);

	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}



/**
 * _assign_alias - assign or overwrite the value of an alias
 *
 * @comm: command line
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_assign_alias(char *comm, param_t *param)
{
	int cut, len;
	char *var, *val, *value;
	aliasl_t *node, *newnode;
	char *errmsg = "alias correct assignement is alias name='value'\n";

	len = _strlen(comm);
	cut = _str_findeq(comm);
	var = _strncut(comm, cut, 0);
	val = _strncut(comm, len - cut - 1, cut + 1);

	if (var == NULL || val == NULL)
		return(1);

	len = _strlen(val);
	if (len < 2)
	{
		write(STDERR_FILENO, errmsg, _strlen(errmsg));
		return (1);
	}
	if (val[0] != 39 || val[len -1] != 39)
	{
		write(STDERR_FILENO, errmsg, _strlen(errmsg));
		return (1);
	}

	value = _strncut(val, len - 2, 1);
	free(val);

	node = param->alias;
	while (node)
	{
		if (_strcmp(node->var, var) == 0)
		{
			node->value = _strdup(value);
			free(var);
			free(value);
			return (0);
		}
		node = node->next;
	}
	node = param->alias;
	newnode = (aliasl_t *)malloc(sizeof(aliasl_t));
	newnode->var = _strdup(var);
	newnode->value = _strdup(value);
	newnode->next = node;
	param->alias = newnode;
	free(var);
	free(value);
	return(0);
}

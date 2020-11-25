#include "hsh.h"

/**
 * _parse_env - add all the environment variable when $is used
 *
 *
 * @comm : intial command token
 * @param: global parameter variable
 *
 * Return: new command line including alias
 */

char *_parse_env(char *comm, param_t *param)
{
	char *newcomm, *isenv;
	int len;
	envl_t *node;

	if (comm == NULL)
		return (NULL);
	len = _strlen(comm);
	if (len < 2 || comm[0] != '$')
		return (comm);
	if (comm[1] == '$')
	{
		newcomm = _strdup(param->pid);
		newcomm = _str_concat_f(newcomm, _strncut(comm, len - 2, 2));
		free(comm);
		return (newcomm);
	}
	if (comm[1] == '?')
	{
		newcomm = _convert_base(param->lastexit, 10, 0);
		newcomm = _str_concat_f(newcomm, _strncut(comm, len - 2, 2));
		free(comm);
		return (newcomm);
	}
	isenv = _strncut(comm, len - 1, 1);
	node = param->envlist;
	while (node)
	{
		if (_strcmp(node->var, isenv) == 0)
		{
			newcomm = _strdup(node->value);
			free(comm);
			free(isenv);
			return (newcomm);
		}
		node = node->next;
	}
	free(comm);
	free(isenv);
	return (_strdup(""));
}

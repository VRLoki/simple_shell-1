#include "hsh.h"


/**
 * _error_cd - display the error message of the function cd.
 *
 * @command: the exit number who make the error.
 * @param: global parameters of the shell.
 *
 * Return: -1 always
 */

int     _error_cd(char **command, param_t *param)
{
	char *dispmess;
	int count = param->count;

	dispmess = _strdup(param->bashname);
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, _convert_base(count, 10, 0));
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, command[0]);
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, "can't cd to ");
	dispmess = _str_concat(dispmess, command[1]);
	dispmess = _str_concat(dispmess, "\n");
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	return (-1);
}


/**
 * _getdest - return the path to destination folder wanted.
 *
 * @home: the variable home.
 * @oldpwd: the variable oldpwd.
 * @path: the destination wanted.
 *
 * Return: the destination directory.
 */

char	*_getdest(char *path, char *home, char *oldpwd)
{

	if (path == NULL)
	{
		return (_strdup(home));
	}
	else if (_strcmp(path, "-") == 0)
	{
		return (_strdup(oldpwd));
	}
	else
	{
		return (_strdup(path));
	}
}


/**
 * _free_cd - free some variables use in cd.
 *
 * @home: the variable home.
 * @pwd: the variable pwd.
 * @oldpwd: the variable oldpwd.
 * @dest: the variable dest.
 *
 * Return: void.
 */

void	_free_cd(char *home, char *pwd, char *oldpwd, char *dest)
{
	if (home != NULL)
		free(home);
	if (pwd != NULL)
		free(pwd);
	if (oldpwd != NULL)
		free(oldpwd);
	if (dest != NULL)
		free(dest);
}


/**
 * _ft_cd - change the current directory
 *
 * @path: the command to execute with the options.
 * @param: global parameters of the shell.
 *
 * Return: 0 (Success) or -1 if fail.
 */

int	_ft_cd(char **path, param_t *param)
{
	envl_t	*node;
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	*dest;

	node = param->envlist;
	while (node != NULL)
	{
		if (_strcmp(node->var, "HOME") == 0)
			home = strdup(node->value);
		if (_strcmp(node->var, "PWD") == 0)
			pwd = strdup(node->value);
		if (_strcmp(node->var, "OLDPWD") == 0)
			oldpwd = strdup(node->value);
		node = node->next;
	}
	dest = _getdest(path[1], home, oldpwd);
	if (chdir(dest) == -1)
	{
		_free_cd(home, pwd, oldpwd, dest);
		return (_error_cd(path, param));
	}
	node = param->envlist;
	while (node != NULL)
	{
		if (_strcmp(node->var, "PWD") == 0)
		{
			free(node->value);
			node->value = _strdup(getcwd(NULL, 4096));
		}
		if (_strcmp(node->var, "OLDPWD") == 0)
		{
			free(node->value);
			node->value = _strdup(pwd);
		}
		node = node->next;
	}
	_free_cd(home, pwd, oldpwd, dest);
	return (0);
}

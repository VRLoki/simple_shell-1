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
	char *dispmess, *conv;
	int count = param->count;

	conv = _convert_base(count, 10, 0);
	dispmess = _strdup(param->bashname);
	dispmess = _str_concat_f(dispmess, ": ");
	dispmess = _str_concat_f(dispmess, conv);
	dispmess = _str_concat_f(dispmess, ": ");
	dispmess = _str_concat_f(dispmess, command[0]);
	dispmess = _str_concat_f(dispmess, ": ");
	dispmess = _str_concat_f(dispmess, "can't cd to ");
	dispmess = _str_concat_f(dispmess, command[1]);
	dispmess = _str_concat_f(dispmess, "\n");
	free(conv);
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
 * @pwd: the current folder
 *
 * Return: the destination directory.
 */

char	*_getdest(char *path, char *home, char *oldpwd, char *pwd)
{

	if (path == NULL)
	{
		if (home == NULL)
		{
			if (pwd == NULL)
				return (getcwd(NULL, 0));
			else
				return (_strdup(pwd));
		}
		return (_strdup(home));
	}
	else if (_strcmp(path, "-") == 0 && oldpwd != NULL)
	{
		return (_strdup(oldpwd));
	}
	else if (_strcmp(path, "-") == 0 && oldpwd == NULL)
	{
		{
			if (pwd == NULL)
				return (getcwd(NULL, 0));
			else
				return (_strdup(pwd));
		}
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
	envl_t	*node = NULL;
	char	*home = NULL, *pwd = NULL, *oldpwd = NULL, *dest = NULL;
	char *temp;

	node = param->envlist;
	while (node != NULL)
	{
		if (_strcmp(node->var, "HOME") == 0)
			home = _strdup(node->value);
		if (_strcmp(node->var, "PWD") == 0)
			pwd = _strdup(node->value);
		if (_strcmp(node->var, "OLDPWD") == 0)
			oldpwd = _strdup(node->value);
		node = node->next;
	}
	dest = _getdest(path[1], home, oldpwd, pwd);
	if (chdir(dest) == -1)
	{
		_free_cd(home, pwd, oldpwd, dest);
		return (_error_cd(path, param));
	}
	temp = getcwd(NULL, 0);
	_add_env_end("PWD", temp, param);
	if (pwd == NULL)
		_add_env_end("OLDPWD", temp, param);
	else
		_add_env_end("OLDPWD", pwd, param);
	free(temp);
	_free_cd(home, pwd, oldpwd, dest);
	_puts_dir(path[1]);
	return (0);
}


/**
 * _puts_dir - display path if needed
 *
 * @path: the path arg
 *
 * Return: void.
 */

void _puts_dir(char *path)
{
	char	*pwd;

	if (path)
	{
		if (_strcmp(path, "-") == 0)
		{
			pwd = getcwd(NULL, 0);
			_puts(pwd);
			_putchar('\n');
			free(pwd);
		}
	}
}

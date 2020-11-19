#include "hsh.h"

/**
 * _free_tab - free a char **.
 *
 * @tab: the char ** to free.
 *
 * Return: void.
 */

void	_free_tab(char **tab)
{
	unsigned int	i;

	if (tab != NULL)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}


/**
 * _init_tab - initialise a char ** to set env.
 *
 * @s1: the new PWD.
 * @s2: the old PWD.
 *
 * Return: the table set or NULL if fail.
 */

char	**_init_tab(char *s1, char *s2)
{
	char		**tab;

	tab = (char **)malloc(sizeof(char *) * 5);
	if (tab == NULL)
	{
		return (NULL);
	}
	tab[0] = _strdup("cd");
	tab[1] = _strdup(s1);
	tab[2] = _strdup(s2);
	tab[3] = _strdup("1");
	tab[4] = NULL;
	return (tab);
}

/**
 * _presetenv - regroup al the parametre to do a setenv.
 *
 * @value: the new pwd value.
 * @oldvalue: the old pwd value.
 * @param: global parameters of the shell.
 *
 * Return: 0 (Success) -1 if fail.
 */

int	_presetenv(char *value, char *oldvalue, param_t *param)
{
	char	**tab;


	tab = _init_tab("OLDPWD", oldvalue);
	free(oldvalue);
	_ft_setenv(tab, param);
	_free_tab(tab);
	tab = _init_tab("PWD", value);
	free(value);
	_ft_setenv(tab, param);
	_free_tab(tab);
	return (0);
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

	node = (envl_t *)malloc(sizeof(envl_t));
	if (node == NULL)
	{
		return (-1);
	}
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
	free(node);
	if (path[1] == NULL)
	{
		chdir(home);
		return (_presetenv(home, pwd, param));
	}
	else if (_strcmp(path[1], ".") == 0)
	{
		free(home);
		free(pwd);
		free(oldpwd);
		return (0);
	}
	else if (_strcmp(path[1], "-") == 0)
	{
		free(home);
		chdir(oldpwd);
		return (_presetenv(oldpwd, pwd, param));
	}
	else if (_strcmp(path[1], "/") == 0)
	{
		free(home);
		chdir("/");
		return (_presetenv("/", pwd, param));
	}
	else if (_strcmp(path[1], "MES IEUCS"))
	{
		return (_presetenv("RIEN", pwd, param));
	}
	else
		return (-1);
}

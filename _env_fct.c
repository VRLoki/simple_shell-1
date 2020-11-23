#include "hsh.h"


/**
 * _initParam - function to initialize the values
 * of the param struct
 *
 * @av: the tab with the arguments.
 * @env: the environnement
 *
 * Return: intialized param struct
 */

param_t *_initParam(char **av, char **env)
{
	param_t *param;

	param = malloc(sizeof(param_t));

	param->count = 0;
	param->fdnb = 0;
	param->bashname = _strdup(av[0]);
	param->alias = NULL;
	param->hist = NULL;
	param->lastexit = 0;
	param->pid = "1111";
	param->envlist = _getEnvList(env);
	return (param);
}


/**
 * _getEnvList - transform the char **env
 * into a envl_t linked list
 *
 * @env: the environnement
 *
 * Return: intialized param struct
 */
envl_t *_getEnvList(char **env)
{
	int i;
	envl_t *new, *head, *tmp;
	char **tok;

	head = NULL;
	i = 0;
	while (env[i])
	{
		new = malloc(sizeof(envl_t));
		if (new == NULL)
			return (NULL);
		tok = _strtow(env[i], "=");
		if (tok[0])
			new->var = _strdup(tok[0]);
		if (tok[1])
			new->value = _strdup(tok[1]);
		free(tok);
		new->next = NULL;
		if (head == NULL)
			head = new;
		else
		{
			tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
	if (_get_env_val("OLDPWD", head) == NULL)
	{
		new = malloc(sizeof(envl_t));
		new->var = "OLDPWD";
		new->value = _strdup(_get_env_val("PWD", head));
		new->next = head;
		head = new;
	}
	return (head);
}

/**
 * _get_env_val - find the value of an env var
 *
 * @var: var to search
 * @head: head of the env list
 *
 * Return: value of var if found, NULL if not
 */
char *_get_env_val(char *var, envl_t *head)
{
	envl_t *tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (_strcmp(tmp->var, var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}




/**
 * _getEnvChar - transform a linked list of
 * env variables into an array of string
 *
 * @head : head of the linked list
 *
 * Return: env in array of string format
 */
char **_getEnvChar(envl_t *head)
{
	int i;
	envl_t *tmp;
	char **env;
	char *var, *value;


	if (head == NULL)
		return (NULL);
	i = 0;
	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}

	env = malloc(sizeof(char *) * (i + 1));

	i = 0;
	tmp = head;
	while (tmp)
	{
		var = _strdup(tmp->var);
		var = _str_concat(var, "=");
		value = _strdup(tmp->value);
		var = _str_concat(var, value);
		env[i] = _strdup(var);
		free(var);
		free(value);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

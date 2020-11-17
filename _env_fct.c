#include "hsh.h"

param_t * _initParam(char **av, char **env)
{
	param_t *param;

	param = malloc(sizeof(param_t));

	param->count = 0;
	param->fdnb = 0;
	param->bashname = _strdup(av[0]);
	param->alias = NULL;
	param->hist = NULL;
	param->lastval = 0;
	param->pid = "1111";
	param->parsed = NULL;
	param->envlist = _getEnvList(env);
	return (param);
}



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

	return (head);

}



char **_getEnvChar(envl_t *head)
{
	int i;
	envl_t *tmp;
	char **env;
	char *var, *value;


	if(head == NULL)
		return (NULL);
	i = 0;
	tmp = head;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}

	env = malloc(sizeof(char *) * (i + 1));

	i = 0;
	tmp = head;
	while(tmp)
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

#include "hsh.h"


/**
 * _freeParam - function to free the parameter variable
 *
 * @param: global parameters variable
 *
 * Return: 0
 */

int _freeParam(param_t *param)
{
	if (param->bashname != NULL)
		free(param->bashname);

	if (param->pid != NULL)
		free(param->pid);

	_free_envlist(param);
	_free_alias(param);
	_free_hist(param);

	if (param->filename != NULL)
		free(param->filename);

	return (0);
}



/**
 * _free_envlist - free the envlist variable
 *
 * @param: global parameters variable
 *
 * Return: 0
 */

int _free_envlist(param_t *param)
{
	envl_t *node, *nodenext;

	node = param->envlist;

	while (node)
	{
		nodenext = node->next;
		free(node->var);
		free(node->value);
		free(node);
		node = nodenext;
	}
	return(0);
}



/**
 * _free_alias - free the alias variable
 *
 * @param: global parameters variable
 *
 * Return: 0
 */

int _free_alias(param_t *param)
{
	aliasl_t *node, *nodenext;

	node = param->alias;

	while (node)
	{
		nodenext = node->next;
		free(node->var);
		free(node->value);
		free(node);
		node = nodenext;
	}
	return (0);
}



/**
 * _free_hist - free the hist variable
 *
 * @param: global parameters variable
 *
 * Return: 0
 */

int _free_hist(param_t *param)
{
	histl_t *node, *nodenext;

	node = param->hist;

	while (node)
	{
		nodenext = node->next;
		free(node->line);
		free(node);
		node = nodenext;
	}
	return (0);
}

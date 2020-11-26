#include "hsh.h"


/**
 * _error_base - generates the first line of error message
 * depending of param mode
 *
 * @param: global parameters of the shell.
 *
 * Return: 2 always
 */

char *_error_base(param_t *param)
{
	char *dispmess, *conv, *file;

	conv = _convert_base(param->count, 10, 0);
	if (param->mode != 2)
	{
		dispmess = _strdup(param->bashname);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
	}
	else
	{
		file = _strdup(param->filename);
		dispmess = _strdup(param->filename);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, file);
		free(file);
	}
	free(conv);
	return (dispmess);

}



/**
 * _add_alias_end - add an alias at the end
 *
 * @var: name of the variable
 * @value: value of the variable
 * @param: global parameters of the shell.
 *
 * Return: 0 if ok, 1 if fails
 */

int _add_alias_end(char *var, char *value, param_t *param)
{
	aliasl_t *node, *new;

	new = (aliasl_t *)malloc(sizeof(aliasl_t));
	if (new == NULL)
		return (1);
	new->var = _strdup(var);
	new->value = _strdup(value);
	new->next = NULL;

	if (param->alias == NULL)
	{
		param->alias = new;
		return (0);
	}

	node = param->alias;
	while (node->next != NULL)
		node = node->next;

	node->next = new;
	return (0);
}

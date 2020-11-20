#include "hsh.h"

/**
 * _ft_unalias - remove an alias from the param
 *
 * @comm: command entered by the user
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_ft_unalias(char **comm, param_t *param)
{
	char *errmsg = "Unalias must be called with a valid arg\n";

	if (comm[1] == NULL)
	{
		write(STDERR_FILENO, errmsg, _strlen(errmsg));
		return (1);
	}
	return (_delete_alias(comm[1], param));
}




/**
 * _delete_alias - delete an alias
 *
 * @comm: name of the alias to delete
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_delete_alias(char *comm, param_t *param)
{
	aliasl_t *head, *old, *next;
	char *errmsg = "Alias to unalias does not exist\n";

	head = param->alias;

	if (head == NULL)
	{
		write(STDERR_FILENO, errmsg, _strlen(errmsg));
		return (1);
	}

	old = head;
	if (_strcmp2(head->var, comm) == 0)
	{
		param->alias = head->next;
		free(old->var);
		free(old->value);
		free(old);
		return (0);
	}

	next = old->next;
	while (next)
	{
		if (_strcmp2(next->var, comm) == 0)
		{
			old->next = next->next;
			free(next->var);
			free(next->value);
			free(next);
			return (0);
		}
		old = next;
		next = old->next;
	}

	write(STDERR_FILENO, errmsg, _strlen(errmsg));
	return (1);

}

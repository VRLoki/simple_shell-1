#include "hsh.h"

/**
 * _atoi_exit - chexk if there is only number in the exit number.
 *
 * @s: the exit number.
 *
 * Return: the exit number or -1 if fail
 */

int	_atoi_exit(char *s)
{
	int			i;
	unsigned long int	nbr;

	i = 0;
	if (s[i] == '+')
		i++;

	nbr = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);

		nbr = nbr * 10 + (s[i] - '0');
		i++;
		if (nbr > INT_MAX)
		{
			return (-1);
		}
	}
	return ((unsigned char)nbr);
}


/**
 * _error_exit - display the error message of the function exit.
 *
 * @command: the exit number who make the error.
 * @param: global parameters of the shell.
 *
 * Return: 2 always
 */

int     _error_exit(char *command, param_t *param)
{
	char *dispmess, *conv, *file;
	int count = param->count;

	conv = _convert_base(count, 10, 0);
	if (param->mode != 2)
	{
	dispmess = _strdup(param->bashname);
	dispmess = _str_concat_f(dispmess, ": ");
	dispmess = _str_concat_f(dispmess, conv);
	dispmess = _str_concat_f(dispmess, ": exit: Illegal number: ");
	dispmess = _str_concat_f(dispmess, command);
	dispmess = _str_concat_f(dispmess, "\n");
	}
	else
	{
		file = _strdup(param->filename);
		dispmess = _strdup(param->filename);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, file);
		dispmess = _str_concat_f(dispmess, ": exit: Illegal number: ");
		dispmess = _str_concat_f(dispmess, command);
		dispmess = _str_concat_f(dispmess, "\n");
		free(file);
	}
	free(conv);
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	return (2);
}


/**
 * _ft_exit - exit the program.
 *
 * @s: the exit number
 * @param: global parameters of the shell.
 * @c: curop
 * @n: nextop
 * @p: parsed
 *
 * Return: 2 if fail
 */

int	_ft_exit(char **s, param_t *param, char *c, char *n, char **p)
{
	int	nbr, lastval;

	if (s[1] == NULL)
	{
		_free_tab(p);
		free(c);
		free(n);
		_free_tab(s);
		_push_hist(param);
		lastval = param->lastexit;
		_freeParam(param);
		_exit(lastval);
	}

	nbr = _atoi_exit(s[1]);
	if (nbr >= 0)
	{
		_free_tab(p);
		free(c);
		free(n);
		_free_tab(s);
		_push_hist(param);
		_freeParam(param);
		_exit((unsigned char)nbr);
	}
	_error_exit(s[1], param);
	return (2);
}

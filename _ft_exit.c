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
	char *dispmess;
	int count = param->count;

	dispmess = _strdup(param->bashname);
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, _convert_base(count, 10, 0));
	dispmess = _str_concat(dispmess, ": exit: Illegal number: ");
	dispmess = _str_concat(dispmess, command);
	dispmess = _str_concat(dispmess, "\n");
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	return (2);
}


/**
 * _ft_exit - exit the program.
 *
 * @s: the exit number
 * @param: global parameters of the shell.
 *
 * Return: 2 if fail
 */

int	_ft_exit(char *s, param_t *param)
{
	int	nbr;

	if (s == NULL)
	{
		_push_hist(param);
		_freeParam(param);
		_exit(0);
	}

	nbr = _atoi_exit(s);
	if (nbr >= 0)
	{
		_push_hist(param);
		_freeParam(param);
		_exit((unsigned char)nbr);
	}
	_error_exit(s, param);
	return (2);
}

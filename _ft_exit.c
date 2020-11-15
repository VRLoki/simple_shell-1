#include "hsh.h"

unsigned char	_atoi_exit(char *s)
{
	int		i;
	unsigned char	nbr;

	i = 0;
	if (s[i] == '+')
	{
		i++;
	}
	nbr = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return (0);
		}
		nbr = nbr * 10 + (s[i] - '0');
		i++;
	}
	return (nbr);
}

bool	_check_zero(char *s)
{
	unsigned int	i;

	i = 0;
	if (s[i] == '+')
	{
		i++;
	}
	while (s[i] == '0')
	{
		i++;
	}
	if (s[i] == '\0')
	{
		return (true);
	}
	return (false);
}

int     _error_exit(char *command, int count, char **env)
{
	char *dispmess;

	dispmess = _strdup(_getenv("_", env));
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, _convert_base(count, 10, 0));
	dispmess = _str_concat(dispmess, ": exit: Illegal number: ");
	dispmess = _str_concat(dispmess, command);
	dispmess = _str_concat(dispmess, "\n");
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
}

int	_ft_exit(char *s, int count, char **env)
{
	unsigned char	nbr;
	char		*num_error;

	if (s == NULL)
	{
		_exit(0);
	}
	num_error = strdup(s);
	nbr = _atoi_exit(num_error);
	if (nbr == 0)
	{
		if (_check_zero(s))
		{
			_exit(nbr);
		}
	}
	else
	{
		_exit(nbr);
	}
	_error_exit(s, count, env); 
	if (num_error != NULL)
	{
		free(num_error);
	}
	return (2);
}

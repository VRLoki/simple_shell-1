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
	while (s[i] >= '0' && s[i] <= '9')
	{
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

void	_ft_exit(char *s)
{
	unsigned char	nbr;
	unsigned int	i;
	unsigned int	j;
	char		*num_error;

	if (s == NULL)
	{
		_exit(0);
	}
	i = 0;
	while (ATOI(s[i]))
	{
		i++;
	}
	j = i;
	while (!ATOI(s[j]))
	{
		j++;
	}
	j -= i;
	num_error = strndup(&s[i], j);
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
	printf("Illegal number: %s\n", num_error);
	if (num_error != NULL)
	{
		free(num_error);
	}
}

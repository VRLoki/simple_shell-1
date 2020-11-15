#include "hsh.h"

int	_isbuiltin(char *comm)
{
	unsigned int	i;
	char		*builtlist[] = {NULL, "exit", "env", "setenv",
		"unsetenv", "cd", "alias", "help", "history", NULL};
	i = 1;
	while (builtlist[i])
	{
		if (_strcmp(comm, builtlist[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

typedef struct	built_fct
{
	int	nbr;
	void	(*ft)(char *status);
}	built_fct_t;

void	(*_get_builtin_fct(int built_nbr))(char *)
{
	int		limit = 2;
	built_fct_t	pft[] = {
		{1, _ft_exit},
//		{2, _ft_env},
//		{3, _ft_setenv},
//		{4, _ft_unsetenv},
//		{5, _ft_cd},
//		{6, _ft_alias},
//		{7, _ft_help},
//		{8, _ft_history},
		{limit, NULL}
	};
	int		i;

	i = 0;
	while (pft[i].nbr < limit)
	{
		if ((pft[i].nbr) == built_nbr)
		{
			return (pft[i].ft);
		}
		i++;
	}

	return (NULL);
}

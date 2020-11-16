#include "hsh.h"

/**
 * main - entry point.
 *
 * @ac: number of arguments.
 * @av: the tab with the arguments.
 * @env: the environnement
 *
 * Return: EXIT_SUCCESS
 */


int main(int ac, char **av, char **env)
{
	if (ac > 1)
		_filemode(av, env);
	if (isatty(STDIN_FILENO))
		_interactive(av, env);
	else
		_noninteractive(av, env);
	return (EXIT_SUCCESS);
}


/**
 * _interactive - execute the shell in interactive mode.
 *
 * @ac: number of arguments.
 * @av: the tab with the arguments.
 * @env: the environnement
 *
 * Return: void
 */

void	_interactive(char **av, char **env)
{
	int	read = 0;
	int	nbw = 0;
	char	*line = NULL;
	size_t	n;
	char	**parsed = NULL;
	int	built_nbr;

	param_t *param;

	int i;
	envl_t *tmp;
	char **envfull;

	param = _initParam(av, env);

	tmp = param->envlist;
	while (tmp)
	{
		printf("%s is %s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}

	envfull = _getEnvChar(param->envlist);
	i = 0;
	while (envfull[i])
	{
		printf("%s\n", envfull[i]);
		i++;
	}
	printf("NAME %s\n", param->bashname);




	while (1)
	{
		param->count++;
		_puts("$: ");
		read = _getline(&line, &n);
		if (read == EOF)
		{
			printf("\n");
			break;
		}
		nbw = 0;
		parsed = _parse_string(line, &nbw);
		line = NULL;
		if (nbw == 0)
			continue;

		built_nbr = _isbuiltin(parsed[0]);
		if (built_nbr != 0)
		{
			_get_builtin_fct(parsed, param);
		}
		else
			_exec_fct(parsed, param);
		_free_grid(parsed, nbw);

	}
	if (line != NULL)
		free(line);
}


/**
 * _noninteractive - execute the shell in noninteractive mode.
 *
 * @ac: number of arguments.
 * @av: the tab with the arguments.
 * @env: the environnement
 *
 * Return: void
 */

void _noninteractive(char **av, char **env)
{
	int read = 0;
	int nbw = 0;
	char *line = NULL;
	size_t n;
	char **parsed = NULL;
	param_t *param;
	int	built_nbr;

	param = _initParam(av, env);

	while ((read = _getline(&line, &n)) != EOF)
	{
		nbw = 0;
		param->count++;
		parsed = _parse_string(line, &nbw);
		if (nbw == 0)
			continue;

		built_nbr = _isbuiltin(parsed[0]);
		if (built_nbr != 0)
		{
			_get_builtin_fct(parsed, param);
		}
		else
			_exec_fct(parsed, param);
	}
	if (line != NULL)
		free(line);
}


/**
 * _filemode - execute the shell in file mode.
 *
 * @ac: number of arguments.
 * @av: the tab with the arguments.
 * @env: the environnement
 *
 * Return: void
 */

void _filemode(char **av, char **env)
{

	int read = 0;
	int nbw = 0;
	char *line = NULL;
	size_t n;
	char **parsed = NULL;
	int fd, err;
	param_t *param;
	int	built_nbr;

	param = _initParam(av, env);

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			err = 126;
		else
			err = 127;
		_error_open(err, av[1], param);
	}

	while ((read = _getlinefile(&line, &n, fd)) != EOF)
	{
		nbw = 0;
		param->count++;
		parsed = _parse_string(line, &nbw);
		if (nbw == 0)
			continue;

		built_nbr = _isbuiltin(parsed[0]);
		if (built_nbr != 0)
		{
			_get_builtin_fct(parsed, param);
		}
		else
			_exec_fct(parsed, param);
	}
	close(fd);
	exit (EXIT_SUCCESS);
}

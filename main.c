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
		_filemode(ac, av, env);
	if (isatty(STDIN_FILENO))
		_interactive(ac, av, env);
	else
		_noninteractive(ac, av, env);
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

void _interactive(int ac, char **av, char **env)
{
	int read = 0;
	int nbw = 0;
	int count = 0;
	char *line = NULL;
	size_t n;
	char **parsed = NULL;

	(void)ac;
	(void)av;

	while (1)
	{
		count++;
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

		if (_isbuiltin(parsed[0]) == 1)
			_exec_builtin();
		else
			_exec_func(parsed, env, count);
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

void _noninteractive(int ac, char **av, char **env)
{
	int read = 0;
	int nbw = 0;
	int count = 0;
	char *line = NULL;
	size_t n;
	char **parsed = NULL;


	(void)ac;
	(void)av;

	while ((read = _getline(&line, &n)) != EOF)
	{
		nbw = 0;
		count++;
		parsed = _parse_string(line, &nbw);
		if (nbw == 0)
			continue;

		if (_isbuiltin(parsed[0]) == 1)
			_exec_builtin(parsed, env, count);
		else
			_exec_func(parsed, env, count);
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

void _filemode(int ac, char **av, char **env)
{

	int read = 0;
	int nbw = 0;
	int count = 0;
	char *line = NULL;
	size_t n;
	char **parsed = NULL;
	int fd, err;

	(void)ac;
	(void)av;


	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			err = 126;
		else
			err = 127;
		_error_open(err, av[1], 0, env);
	}

	while ((read = _getlinefile(&line, &n, fd)) != EOF)
	{
		nbw = 0;
		count++;
		parsed = _parse_string(line, &nbw);
		if (nbw == 0)
			continue;

		if (_isbuiltin(parsed[0]) == 1)
			_exec_builtin(parsed, env, count);
		else
			_exec_func(parsed, env, count);
	}
	close(fd);
	exit (EXIT_SUCCESS);
}

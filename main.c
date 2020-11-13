#include "hsh.h"




int main(int ac, char **av, char **env)
{
/*	int read = 0;
	int nbw = 0;
	int count = 0;
	char *line = NULL;
	size_t n;
	char **parsed = NULL;
	int fd;
	int err;
	FILE *open_file;
*/
	if (ac == 2)
		_filemode(ac, av, env);
	if (isatty(STDIN_FILENO))
		_interactive(ac, av, env);
	else
		_noninteractive(ac, av, env);
	return (EXIT_SUCCESS);
}



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
		printf("$:%i ", count);
		read = getline(&line, &n, stdin);
		if (read == EOF)
		{
			printf("\n");
			break;
		}
		nbw = 0;
		parsed = _parse_string(line, &nbw);
		if (nbw == 0)
			continue;

		if (_isbuiltin(parsed[0]) == 1)
			_exec_builtin();
		else
			_exec_func(parsed, env, count);
		_free_grid(parsed, nbw);

	}
	free(line);
}




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

	while ((read = getline(&line, &n, stdin)) != EOF)
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
	free(line);

}




void _filemode(int ac, char **av, char **env)
{
/*		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				err = 126;
			else
				err = 127;
			_error_open(err, av[1], 0, env);
		}

		while ((read = getline(&line, &n, open_file)) != EOF)
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
			return (EXIT_SUCCESS);
*/
	(void)ac;
	(void)env;
	printf("To be done %s", av[1]);
	exit(EXIT_SUCCESS);

}

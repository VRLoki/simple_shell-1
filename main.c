#include "hsh.h"




int main(int ac, char **av, char **env)
{
	int read = 0;
	int nbw = 0;
	int count = 0;
	char *line = NULL;
	size_t n;
	char **parsed = NULL;

	if (ac > 1)
	{
		printf("hsh used with file - Non interactive mode %s\n", av[1]);
		exit(0);
	}
	if (isatty(STDIN_FILENO))
	{
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

			_exec_func(parsed, env);
			_free_grid(parsed, nbw);

		}
		free(line);
	}
	else
	{
		while ((read = getline(&line, &n, stdin)) != EOF)
		{
			nbw = 0;
			count++;
			parsed = _parse_string(line, &nbw);
			if (nbw == 0)
				continue;

			_exec_func(parsed, env);
			_free_grid(parsed, nbw);

		}
		free(line);
	}
	return (0);
}

#include "hsh.h"




int main(int ac, char **av)
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
			printf("$ ");
			count++;
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

			_exec_func(parsed[0], parsed, NULL);
			_free_grid(parsed, nbw);


		}
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

			_exec_func(parsed[0], parsed, NULL);
			_free_grid(parsed, nbw);
		}
	}

	return (0);
}


int _exec_func(char *comm, char **commarg, char **en)
{

	int status = 0;
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: Children process failed");
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(comm, commarg, en) == -1)
		{
			exit(2);
		}
	}
	else
		wait(&status);

	return (0);
}

#include "hsh.h"


int main(int ac, char *av)
{
	int read = 0;
	int nbw = 0;
	int count = 0;
	char *line = NULL;
	size_t n;
	char *str;
	char *token;
	pid_t child_pid;
	int status;
	char **parsed = NULL;
	char *argv[10];

	if (ac > 1)
	{
		printf("hsh used with file to read - Non interactive mode\n");
		exit(0);
	}
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			printf("$ ");

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

			exec_func(parsed[0], parsed, NULL);
			_free_grid(parsed, nbw);


		}
	}
	else
	{
		while ((read = getline(&line, &n, stdin)) != EOF)
		{
			if (strlen(line) == 1)
				continue;

			line[strlen(line)-1] = 0;

			nbw = 0;
			token = strtok(line, " ");
			while (token != NULL)
			{
				argv[nbw]  = token;
				nbw++;
				token = strtok(NULL, " ");
			}
			argv[nbw] = NULL;

			exec_func(argv[0], argv, NULL);
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
		if (execve(comm, commarg, en) == -1);
		    exit(2);
	}
	else
		wait(&status);

}

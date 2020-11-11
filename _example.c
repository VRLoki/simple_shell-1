#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int read;
	int i;
	char *line;
	size_t n;
	char *str;
	char *token;
	pid_t child_pid;
	int status;
	char *argv[10];

	while (1)
	{
		line = 0;
		printf("#cisfun$ ");
		read = getline(&line, &n, stdin);
		if (read == -1)
			printf("Error");

		if (strlen(line) == 1)
			continue;

		line[strlen(line)-1] = 0;

		i = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			argv[i]  = token;
			i++;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;


		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}

		if (child_pid == 0)
		{
			execve(argv[0], argv, NULL);
		}
		else
			wait(&status);

	}


	return (0);
}

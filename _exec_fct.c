#include "hsh.h"



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
			perror("test");
			printf("Error number %i\n", errno);
			exit(errno);
		}
	}
	else
		wait(&status);

	return (0);
}

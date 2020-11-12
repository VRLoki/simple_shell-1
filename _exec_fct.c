#include "hsh.h"



int _exec_func(char **parsed, char **env)
{
	int status = 0, exit_status = 0;
	pid_t child_pid;
	char *mypath;
	char *command;

	child_pid = fork();
	mypath = _getenv("PATH", env);
	command = _getfullpath(parsed[0], mypath);

	if (child_pid == -1)
	{
		perror("Error: Children process failed");
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(command, parsed, env) == -1)
		{
			perror("test");
			printf("Error number %i\n", errno);
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			WEXITSTATUS(status);
		exit_status = WEXITSTATUS(status);
		printf("exit_status %i\n", exit_status);
	}
	return (exit_status);
}






char *_getfullpath(char *name, char *mypath)
{
	char *fullname = NULL;
	char *fullnamepath = NULL;
	char *token = NULL;
	char *copypath;
	struct stat st;

	if (stat(name, &st) == 0)
		return (name);

	if (mypath == NULL || mypath[0] == ':' || (name[0] == '.' && name[1] == '/'))
		return(name);

	fullname = _str_concat("/", name);
	copypath = _strdup(mypath);

	token = strtok(copypath, ":");
	while (token != NULL)
	{
		fullnamepath = _str_concat(token, fullname);
		if (stat(fullnamepath, &st) == 0)
		{
			free(fullname);
			return(fullnamepath);
		}
		token = strtok(NULL, ":");
		free(fullnamepath);
	}
	free(fullname);
	free(copypath);
	return(name);
}

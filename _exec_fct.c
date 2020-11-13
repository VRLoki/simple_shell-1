#include "hsh.h"



int _exec_func(char **parsed, char **env, int count)
{
	int status = 0, exit_status = 0;
	pid_t child_pid;
	char *mypath;
	char *command;

	mypath = _getenv("PATH", env);
	command = _getfullpath(parsed[0], mypath);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: Children process failed");
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(command, parsed, env) == -1)
		{
			_error_func(errno, command, count, env);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			WEXITSTATUS(status);
		}
		exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}





typedef struct	error_mess
{
	int	nbr_error;
	int	n_err_sh;
	char	*m_error;
}	error_mess_t;




int	_error_func(int errnb, char *command, int count, char **env)
{
	unsigned int	i;
	char *dispmess;
	error_mess_t	error_mess[] = {
		{2, 127, "not found"},
		{13, 126, "Permission denied"},
	};

	dispmess = _strdup(_getenv("_", env));
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, _convert_base(count, 10, 0));
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, command);
	dispmess = _str_concat(dispmess, ": ");

	i = 0;
	while (error_mess[i].nbr_error)
	{
		if ((error_mess[i].nbr_error) == errnb)
		{
			dispmess = _str_concat(dispmess, error_mess[i].m_error);
			dispmess = _str_concat(dispmess, "\n");
			write(STDERR_FILENO, dispmess, _strlen(dispmess));
			free(dispmess);
			exit (error_mess[i].n_err_sh);
		}
		i++;
	}
	dispmess = _str_concat(dispmess, "Error to add");
	dispmess = _str_concat(dispmess, "\n");
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	exit (EXIT_FAILURE);
}





int	_error_open(int errnb, char *command, int count, char **env)
{
	char *dispmess;

	dispmess = _strdup(_getenv("_", env));
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, _convert_base(count, 10, 0));
	dispmess = _str_concat(dispmess, ": Can't open ");
	dispmess = _str_concat(dispmess, command);
	dispmess = _str_concat(dispmess, "\n");
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	exit (errnb);
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

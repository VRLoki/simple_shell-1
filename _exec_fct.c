#include "hsh.h"

/**
 * _exec_fct - execute the commande pass by parsed
 *
 * @parsed: the commande to execute.
 * @param: global parameters of the shell.
 *
 * Return: the exit status (Always)
 */

int _exec_fct(char **parsed, param_t *param)
{
	int status = 0, exit_status = 0;
	pid_t child_pid;
	char *mypath;
	char *command;
	char **envfull = _getEnvChar(param->envlist);

	mypath = _getenv("PATH", envfull);
	command = _getfullpath(parsed[0], mypath);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: Children process failed");
		exit(1);
	}
	if (child_pid == 0)
	{
		if (execve(command, parsed, envfull) == -1)
		{
			_error_fct(errno, command, param);
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




int	_error_fct(int errnb, char *command, param_t *param)
{
	unsigned int	i;
	char *dispmess;

	error_mess_t	error_mess[] = {
		{2, 127, "not found"},
		{13, 126, "Permission denied"},
	};

	dispmess = _strdup(param->bashname);
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, _convert_base(param->count, 10, 0));
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
			exit(error_mess[i].n_err_sh);
		}
		i++;
	}
	dispmess = _str_concat(dispmess, "Error to add");
	dispmess = _str_concat(dispmess, "\n");
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	exit (EXIT_FAILURE);
}


/**
 * _error_open - Display an error message.
 *
 * @errnb: the error number.
 * @command: the name of the command who is failling.
 * @param: global parameters of the shell.
 *
 * Return: (Always)
 */

int	_error_open(int errnb, char *command, param_t *param)
{
	char *dispmess;

	dispmess = _strdup(param->bashname);
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, _convert_base(param->count, 10, 0));
	dispmess = _str_concat(dispmess, ": Can't open ");
	dispmess = _str_concat(dispmess, command);
	dispmess = _str_concat(dispmess, "\n");
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	exit (errnb);
}


/**
 * _getfullpath - get the full path of a command.
 *
 * @name: the command.
 * @mypath: .
 *
 * Return: (Always)
 */

char *_getfullpath(char *name, char *mypath)
{
	char *fullname = NULL;
	char *fullnamepath = NULL;
	char *token = NULL;
	char *copypath;
	struct stat st;

	printf("name = [%s]\n", name);
	printf("path = [%s]\n", mypath);
	if (stat(name, &st) == 0)
		return (name);

	if (mypath == NULL || mypath[0] == ':'
		|| (name[0] == '.' && name[1] == '/'))
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

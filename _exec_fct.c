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
	char *mypath, *command, *tmp;
	char **envfull;

	envfull = _getEnvChar(param->envlist);
	mypath = _getenv("PATH", envfull);
	tmp = _getfullpath(parsed[0], mypath);
	command = _strdup(tmp);
	free(tmp);
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
		if (envfull)
			_free_tab(envfull);
		if (command)
			free(command);
		wait(&status);
		if (WIFEXITED(status))
		{
			WEXITSTATUS(status);
		}
		exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}






/**
 * _error_fct - print an error message
 *
 * @errnb: error number input
 * @command: command failing
 * @param : global parameters structure
 *
 * Return: the exit status (Always)
 */
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
	exit(EXIT_FAILURE);
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
	exit(errnb);
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
	char **splitpath;
	int i;
	struct stat st;

	if (mypath == NULL || (name[0] == '.' && name[1] == '/'))
		return (name);

	fullname = _str_concat("/", name);
	splitpath = _strtow2(mypath, ":");

	i = 0;
	while (splitpath[i] != NULL)
	{
		if (_strlen(splitpath[i]) == 0)
			fullnamepath = _strdup(name);
		else
			fullnamepath = _str_concat(splitpath[i], fullname);

		if (stat(fullnamepath, &st) == 0)
		{
			_free_tab(splitpath);
			free(fullname);
			return (fullnamepath);
		}

		free(fullnamepath);
		i++;
	}
	free(fullname);
	_free_tab(splitpath);
	return (name);

}


/**
 * _contains_char - determine if a string contains a character
 *
 * @str: string to parse
 * @c: character to find
 *
 * Return: 0 if not in, 1 if in
 */

int _contains_char(char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

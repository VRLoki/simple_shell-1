#include "hsh.h"

/**
 * _exec_fct - execute the commande pass by parsed
 *
 * @parsed: the commande to execute.
 * @param: global parameters of the shell.
 * @c : curop
 * @n : nextop
 * @p : parsed string intial
 *
 * Return: the exit status (Always)
 */

int _exec_fct(char **parsed, param_t *param, char *c, char *n, char **p)
{
	int status = 0, exit_status = 0;
	pid_t child_pid;
	char *mypath, *command;
	char **envfull;

	envfull = _getEnvChar(param->envlist);
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
			_free_tab(envfull);
			_eft(errno, command, parsed, param, c, n, p);
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
 *_eft - print an error message
 *
 * @nb: error number input
 * @co: command failing
 * @pd: parsed string
 * @pm : global parameters structure
 * @p: parsed string
 * @c: curop
 * @n: nextop
 *
 *
 * Return: the exit status (Always)
 */
int _eft(int nb, char *co, char **pd, param_t *pm, char *c, char *n, char **p)
{
	unsigned int	i;
	char *dispmess;

	error_mess_t	error_mess[] = {
		{2, 127, "not found"},
		{13, 126, "Permission denied"},
	};
	dispmess = _error_base(pm);
	dispmess = _str_concat_f(dispmess, ": ");
	dispmess = _str_concat_f(dispmess, co);
	dispmess = _str_concat_f(dispmess, ": ");
	_free_tab(p);
	free(co);
	free(c);
	free(n);
	_free_tab(pd);
	_freeParam(pm);
	i = 0;
	while (error_mess[i].nbr_error)
	{
		if ((error_mess[i].nbr_error) == nb)
		{
			dispmess = _str_concat_f(dispmess, error_mess[i].m_error);
			dispmess = _str_concat_f(dispmess, "\n");
			write(STDERR_FILENO, dispmess, _strlen(dispmess));
			free(dispmess);
			exit(error_mess[i].n_err_sh);
		}
		i++;
	}
	dispmess = _str_concat_f(dispmess, "Error to add");
	dispmess = _str_concat_f(dispmess, "\n");
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
	char *dispmess, *conv, *file;

	conv = _convert_base(param->count, 10, 0);
	if (param->mode != 2)
	{	dispmess = _strdup(param->bashname);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
		dispmess = _str_concat_f(dispmess, ": Can't open ");
		dispmess = _str_concat_f(dispmess, command);
		dispmess = _str_concat_f(dispmess, "\n");
	}
	else
	{
		file = _strdup(param->filename);
		dispmess = _strdup(param->filename);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, file);
		dispmess = _str_concat_f(dispmess, ": Can't open ");
		dispmess = _str_concat_f(dispmess, command);
		dispmess = _str_concat_f(dispmess, "\n");
		free(file);
	}
	free(conv);
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	_freeParam(param);
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
		return (_strdup(name));

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
	return (_strdup(name));

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

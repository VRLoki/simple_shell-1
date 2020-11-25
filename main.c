#include "hsh.h"

/**
 * main - entry point.
 *
 * @ac: number of arguments.
 * @av: the tab with the arguments.
 * @env: the environnement
 *
 * Return: EXIT_SUCCESS
 */


int main(int ac, char **av, char **env)
{
	int fd, err, lastval;
	param_t *param;

	param = _initParam(av, env);
	if (ac > 1)
	{	fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				err = 126;
			else
				err = 127;
			free(param);
			_error_open(err, av[1], param);
		}
		else
		{
			param->mode = 2;
			param->fdnb = fd;
			param->filename = _strdup(av[1]);
		}
	}
	else if (isatty(STDIN_FILENO))
	{
		param->mode = 0;
		param->fdnb = STDIN_FILENO;
	}
	else
	{
		param->mode = 1;
		param->fdnb = STDIN_FILENO;
	}

	lastval = _launchShell(param);
	return (lastval);
}


/**
 * _launchShell - launch and exit the shell loop
 *
 * @param: parameter variable
 *
 * Return: EXIT_SUCCESS
 */

int _launchShell(param_t *param)
{
	int exitval;

	signal(SIGINT, _siginthandler);

/*
 * if (param->mode == 0)
 *	_pull_hist(param);
 */
	_prompt(param);
	_shell_loop(param);
/*
 * if(param->mode == 0)
 *	_push_hist(param);
 */
	if (param->mode == 0)
		_putchar('\n');
	if (param->mode == 2)
		close(param->fdnb);
	exitval = param->lastexit;
	_freeParam(param);
	return (exitval);
}


/**
 * _shell_loop - main loop for Shell
 *
 * @param: parameter variable
 *
 * Return: EXIT_SUCCESS
 */

int _shell_loop(param_t *param)
{
	int     read, read2 = 0, nbw, nbw2, checkgramm;
	char    *line = NULL, *part;
	size_t  n;
	char    **parsed, **parsed2;

	while ((read = _getlinefile(&line, &n, param->fdnb)) != EOF)
	{
		part = _strdup(line);
		nbw = 0;
		param->count++;
		parsed = _parse_string2(line, &nbw, param);
		checkgramm = _check_grammar(parsed, nbw, param);
		while (checkgramm == 1)
		{
			_prompt2(param);
			read2 = _getlinefile(&line, &n, param->fdnb);
			part = _str_concat_hist(part, line);
			param->count++;
			if (read2 == EOF)
			{
				_error_EOF(param);
				break;
			}
			read2 = 0;
			nbw2 = 0;
			parsed2 = _parse_string2(line, &nbw2, param);
			parsed = _concat_parsed(parsed, &nbw, parsed2, &nbw2);
			checkgramm = _check_grammar(parsed, nbw, param);
		}
		_add_hist_line(part, param);
		if (checkgramm == 3)
			parsed = _removelast(parsed, &nbw);
		if (nbw == 0 || checkgramm == 2 || read2 == EOF)
		{
			_prompt(param);
			continue;
		}
		_core_exec(parsed, nbw, param);
	}
	return (1);
}



/**
 * _core_exec - main loop for Shell
 *
 * @parsed : parsed string
 * @nbw : number of tokens
 * @param: parameter variable
 *
 * Return: EXIT_SUCCESS
 */

int _core_exec(char **parsed, int nbw, param_t *param)
{
	_exec_string(parsed, nbw, param);
	_free_grid(parsed, nbw);
	_prompt(param);


	return (1);
}








/**
 * _siginthandler - signal handler
 *
 * @signum: int
 */
void _siginthandler(int signum)
{
	(void) signum;
	write(0, "\n", 1);
	_puts("$: ");
}

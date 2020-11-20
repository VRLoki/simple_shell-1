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
	int fd, err;
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

	_launchShell(param);
	return (EXIT_SUCCESS);
}


/**
 * _launchShell - main loop for Shell
 *
 * @param: parameter variable
 *
 * Return: EXIT_SUCCESS
 */

int _launchShell(param_t *param)
{
	int     read = 0, nbw = 0, checkgramm;
	char    *line = NULL;
	size_t  n;
	char    **parsed = NULL;

	signal(SIGINT, _siginthandler);
	_prompt(param);
	while ((read = _getlinefile(&line, &n, param->fdnb)) != EOF)
	{
		nbw = 0;
		param->count++;
		parsed = _parse_string2(line, &nbw, param);
		checkgramm = _check_grammar(parsed, nbw, param);


		if (nbw == 0 || checkgramm == 2)
		{
			_prompt(param);
			continue;
		}

		_exec_string(parsed, nbw, param);
		_free_grid(parsed, nbw);
		_prompt(param);

	}
	if (param->mode == 0)
		_putchar('\n');
	if (line != NULL)
		free(line);
	if (param->mode == 2)
		close(param->fdnb);
	return (EXIT_SUCCESS);
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


/**
 * _prompt - display promter
 *
 * @param: parameter variable
 */

void _prompt(param_t *param)
{
	if (param->mode == 0)
		_puts("$: ");
}

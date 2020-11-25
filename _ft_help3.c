#include "hsh.h"


/**
 * _help_all - display the list of help pages
 *
 * Return: Void
 */

void	_help_all(void)
{
	_puts("alias [-p] [name[=value] ... ]\n");
	_puts("cd [dir]\n");
	_puts("env  [-]\n");
	_puts("exit [n]\n");
	_puts("help [PATTERN]\n");
	_puts("history\n");
	_puts("setenv [VARIABLE] [VALUE]\n");
	_puts("unalias name [name ...]\n");
	_puts("unsetenv [VARIABLE]\n");
}



/**
 * _help_error - display error message for help
 *
 * @command : command passed
 * @param : global parameters variable
 *
 * Return: Void
 */

void	_help_error(char *command, param_t *param)
{
	char *dispmess, *conv, *file;

	conv = _convert_base(param->count, 10, 0);
	file = _strdup(param->filename);
	if (param->mode != 2)
	{
		dispmess = _strdup(param->bashname);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
		dispmess = _str_concat_f(dispmess, ": No help topics match \"");
		dispmess = _str_concat_f(dispmess, command);
		dispmess = _str_concat_f(dispmess, "\"\n");
	}
	else
	{
		dispmess = _strdup(file);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, file);
		dispmess = _str_concat_f(dispmess, ": No help topics match \"");
		dispmess = _str_concat_f(dispmess, command);
		dispmess = _str_concat_f(dispmess, "\"\n");
	}
	free(file);
	free(conv);
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
}

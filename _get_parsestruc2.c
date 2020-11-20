#include "hsh.h"



/**
 * _error_syntax - Display an error message.
 *
 * @command: the name of the command who is failling.
 * @param: global parameters of the shell.
 *
 * Return: 2 (Always)
 */

int _error_syntax(char *command, param_t *param)
{
	char *dispmess;

	dispmess = _strdup(param->bashname);
	dispmess = _str_concat(dispmess, ": ");
	dispmess = _str_concat(dispmess, _convert_base(param->count, 10, 0));
	dispmess = _str_concat(dispmess, ": Syntax error: \"");
	dispmess = _str_concat(dispmess, command);
	dispmess = _str_concat(dispmess, "\" unexpected\n");
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	return (2);
}

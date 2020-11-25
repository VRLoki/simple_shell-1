#include "hsh.h"


/**
 * _error_base - generates the first line of error message
 * depending of param mode
 *
 * @param: global parameters of the shell.
 *
 * Return: 2 always
 */

char *_error_base(param_t *param)
{
	char *dispmess, *conv, *file;

	conv = _convert_base(param->count, 10, 0);
	if (param->mode != 2)
	{
		dispmess = _strdup(param->bashname);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
	}
	else
	{
		file = _strdup(param->filename);
		dispmess = _strdup(param->filename);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, conv);
		dispmess = _str_concat_f(dispmess, ": ");
		dispmess = _str_concat_f(dispmess, file);
		free(file);
	}
	free(conv);
	return (dispmess);

}

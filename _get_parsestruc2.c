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

	if (param->mode != 2)
	{
		dispmess = _strdup(param->bashname);
		dispmess = _str_concat(dispmess, ": ");
		dispmess = _str_concat(dispmess, _convert_base(param->count, 10, 0));
		dispmess = _str_concat(dispmess, ": Syntax error: \"");
		dispmess = _str_concat(dispmess, command);
		dispmess = _str_concat(dispmess, "\" unexpected\n");
	}
	else
	{
		dispmess = _strdup(param->filename);
		dispmess = _str_concat(dispmess, ": ");
		dispmess = _str_concat(dispmess, _convert_base(param->count, 10, 0));
		dispmess = _str_concat(dispmess, ": ");
		dispmess = _str_concat(dispmess, _strdup(param->filename));
		dispmess = _str_concat(dispmess, ": Syntax error: \"");
		dispmess = _str_concat(dispmess, command);
		dispmess = _str_concat(dispmess, "\" unexpected\n");
	}
	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	return (2);

}



/**
 * _gramm_ret - Free used char * and return ret
 *
 * @curop: string1
 * @nextop: string 2
 * @ret: return int
 *
 * Return: ret
 */

int _gramm_ret(char *curop, char *nextop, int ret)
{
	free(curop);
	free(nextop);
	return (ret);
}





/**
 * _removelast - remove last token of a parsed list
 *
 * @parsed: token list
 * @nbw: intial length of parsed
 *
 * Return: new parsed list
 */

char **_removelast(char **parsed, int *nbw)
{
	char **newparsed;
	int i;

	newparsed = malloc(sizeof(char *) * (*nbw));
	if (newparsed == NULL)
		return (NULL);

	*nbw -= 1;
	for (i = 0; i < *nbw; i++)
	{
		newparsed[i] = _strdup(parsed[i]);
		free(parsed[i]);
	}
	newparsed[i] = NULL;
	free(parsed[i]);
	free(parsed);
	return (newparsed);
}




/**
 * _concat_parsed - concatenates 2 token lists
 *
 * @parsed: token list1
 * @nbw: length of parsed1
 * @parsed2: token list2
 * @nbw2: length of parsed2
 *
 *
 * Return: new parsed list
 */

char **_concat_parsed(char **parsed, int *nbw, char **parsed2, int *nbw2)
{
	char **newparsed;
	int i;


	newparsed = malloc(sizeof(char *) * (*nbw + *nbw2 + 1));
	if (newparsed == NULL)
		return (NULL);

	for (i = 0; i < *nbw; i++)
	{
		newparsed[i] = _strdup(parsed[i]);
		free(parsed[i]);
	}
	free(parsed);

	for (i = 0; i < *nbw2; i++)
	{
		newparsed[i + *nbw] = _strdup(parsed2[i]);
		free(parsed2[i]);
	}
	free(parsed2);
	newparsed[*nbw + *nbw2] = NULL;
	*nbw = *nbw + *nbw2;
	return (newparsed);
}





/**
 * _error_EOF - Display an error message.
 *
 * @param: global parameters of the shell.
 *
 * Return: 2 (Always)
 */

int _error_EOF(param_t *param)
{
	char *dispmess;

	if (param->mode != 2)
	{
		dispmess = _strdup(param->bashname);
		dispmess = _str_concat(dispmess, ": ");
		dispmess = _str_concat(dispmess, _convert_base(param->count, 10, 0));
		dispmess = _str_concat(dispmess, ": Syntax error: end of file unexpected\n");
	}
	else
	{
		dispmess = _strdup(param->filename);
		dispmess = _str_concat(dispmess, ": ");
		dispmess = _str_concat(dispmess, _convert_base(param->count, 10, 0));
		dispmess = _str_concat(dispmess, ": ");
		dispmess = _str_concat(dispmess, _strdup(param->filename));
		dispmess = _str_concat(dispmess, ": Syntax error: end of file unexpected\n");
	}

	write(STDERR_FILENO, dispmess, _strlen(dispmess));
	free(dispmess);
	return (2);

}

#include "hsh.h"



/**
 * _exec_string - execute a valid command line
 *
 * @parsed: input parsed line
 * @nbw: number of token in the parsed line
 * @param: global parameter variable
 *
 * Return: 0 if correct, 2 if not
 */

int _exec_string(char **parsed, int nbw, param_t *param)
{
	int cur = -1;
	int temp = -1;
	int built_nbr, lastexit;
	char *nextop, *curop;
	char **comm = NULL;

	curop = _strdup(";");
	lastexit = 0;
	while (temp < nbw)
	{
		cur += 1;
		nextop = _strdup(_get_nextop(parsed, &cur));
		if (_strcmp(curop, "#") == 0)
			return (_gramm_ret(curop, nextop, param->lastexit));
		if (_exec_need(curop, lastexit) == 1)
		{
			comm = _getcomm(parsed, temp, cur);
			if (comm[0] != NULL)
			{
			built_nbr = _isbuiltin(comm[0]);
			if (built_nbr != 0)
				lastexit = _get_b_fct(comm, param, curop, nextop, parsed);
			else
				lastexit = _exec_fct(comm, param, curop, nextop, parsed);
			}
			_free_tab(comm);
		}
		param->lastexit = lastexit;
		free(curop);
		curop = _strdup(nextop);
		free(nextop);
		temp = cur;
	}
	free(curop);
	return (0);
}




/**
 * _getcomm - extract a comm array of string from a parsed line
 *
 * @parsed: parsed string
 * @from: token from
 * @to: token to
 *
 * Return: command line, NULL terminated
 */

char **_getcomm(char **parsed, int from, int to)
{
	int i;
	char **comm;

	comm = malloc(sizeof(char *) * (to - from));
	if (comm == NULL)
		return (NULL);
	for (i = 0; i < to - from - 1; i++)
		comm[i] = _strdup(parsed[i + from + 1]);
	comm[i] = NULL;
	return (comm);
}





/**
 * _exec_need - determine if a command has to be executed
 *
 * @curop: current operator
 * @lastexit: current lastexit
 *
 * Return: 1 if need to execute, else 0
 */

int _exec_need(char *curop, int lastexit)
{
	if (_strcmp(curop, ";") == 0)
		return (1);
	if (_strcmp(curop, "&&") == 0 && lastexit == 0)
		return (1);
	if (_strcmp(curop, "||") == 0 && lastexit != 0)
		return (1);
	return (0);
}








/**
 * _check_grammar - check if the command line is valid
 * and display an error message if not
 *
 * @parsed: input parsed line
 * @nbw: number of token in the parsed line
 * @param: global parameter variable
 *
 * Return: 0 if correct, 1 if need more line, 2 if wrong, 3 if final ';'
 */

int _check_grammar(char **parsed, int nbw, param_t *param)
{
	int cur = -1;
	int temp = -1;
	char *nextop, *curop;

	if (nbw == 0)
		return (0);

	curop = _strdup(";");
	while (cur < nbw)
	{
		cur += 1;
		nextop = _strdup(_get_nextop(parsed, &cur));

		if (_strcmp(nextop, "#") == 0)
			return (_gramm_ret(curop, nextop, 0));
		if (cur - temp <= 1 && _strcmp(nextop, "END") == 0)
		{
			if (_strcmp(curop, ";") == 0)
				return (_gramm_ret(curop, nextop, 3));
			if (_strcmp(curop, "&&") == 0)
				return (_gramm_ret(curop, nextop, 1));
			if (_strcmp(curop, "||") == 0)
			return (_gramm_ret(curop, nextop, 1));
		}
		if (cur - temp <= 1)
		{
			_error_syntax(nextop, param);
			param->lastexit = 2;
			return (_gramm_ret(curop, nextop, 2));
		}
		free(curop);
		curop = _strdup(nextop);
		free(nextop);
		temp = cur;
	}
	free(curop);
	return (0);
}












/**
 * _get_nextop - find the next logic operator in a
 * parsed string
 *
 * @parsed: input parsed line
 * @cur: cursor number
 *
 * Return: next logic operator
 */

char *_get_nextop(char **parsed, int *cur)
{
	char *NEXT = ";";
	char *AND = "&&";
	char *OR = "||";
	char *STOP = "#";
	char *FIN = "END";

	while (parsed[*cur])
	{
		if (_strcmp(parsed[*cur], NEXT) == 0)
			return (NEXT);
		if (_strcmp(parsed[*cur], AND) == 0)
			return (AND);
		if (_strcmp(parsed[*cur], OR) == 0)
			return (OR);
		if (_strcmp(parsed[*cur], STOP) == 0)
			return (STOP);
		*cur += 1;
	}
	return (FIN);
}

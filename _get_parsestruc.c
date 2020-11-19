#include "hsh.h"

/**
 * _get_ope - populate the operation array of int
 * and the number of args array of int
 *
 * @line: input line
 * @ope: operation array
 * @nbarg: number of arg array
 * @nbw: number of words in line
 *
 * Return: number of commands
 */

int *_get_ope (char **line, int **ope, int **nbarg, int nbw)
{
	int i = 0;
	int nbcomm;

	if (nbw == 0)
	{
		*ope = NULL;
		*nbarg = NULL;
		return (0);
	}

	nbcomm = 1;
	while (line[i])
	{
		if (_strcmp(line[i], ";") == 0)
			nbcomm += 1;
		if (_strcmp(line[i], "&&") == 0)
			nbcomm += 1;
		if (_strcmp(line[i], "||") == 0)
			nbcomm += 1;
	}

}

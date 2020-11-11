#include "hsh.h"



/**
 * free_grid - frees a 2 dimensional grid
 *
 * @grid : grid to be freed
 * @height : grid height
 *
 * Return: None
 */

void _free_grid(char **grid, int height)
{
	int i;

	for (i = 0; i < height; i++)
		free(grid[i]);
	free(grid);
}





/**
 * _parse_string - find all the words from a string and
 * store them in a grid
 *
 * @string : string parsed
 * @nbw : number of words
 *
 * Return: created char **
 */


char **_parse_string(char *string, int *nbw)
{
	int i;
	char *token, *dups;
	char **parsed;
	const char *sep = " \n\t\a\r\v";

	dups = _strdup(string);
	if (dups == NULL)
		return (NULL);

	token = strtok(dups, sep);
	while (token != NULL)
	{
		(*nbw)++;
		token = strtok(NULL, sep);
	}
	free(dups);

	parsed = malloc(sizeof(char *) * (*nbw + 1));
	if (parsed == NULL)
		return (NULL);

	dups = _strdup(string);
	if (dups == NULL)
		return (NULL);

	token = strtok(dups, sep);
	for (i = 0; i < (*nbw); i++)
	{
		parsed[i] = _strdup(token);
		if (parsed[i] == NULL)
		{
			_free_grid(parsed, i - 1);
			free(dups);
			return (NULL);
		}
		token = strtok(NULL, sep);
	}
	parsed[i] = NULL;
	free(dups);
	return (parsed);
}

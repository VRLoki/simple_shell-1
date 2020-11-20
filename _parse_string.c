#include "hsh.h"



/**
 * _free_grid - frees a 2 dimensional grid
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



/**
 * _parse_string2 - find all the words from a string and
 * store them in a grid using _strtow
 *
 * @string : string parsed
 * @nbw : number of words
 *
 * Return: created char **
 */

char **_parse_string2(char *string, int *nbw, param_t *param)
{
	char *del = " \n\t\a\r\v";
	char **comm;
	char **aliascomm;
	aliasl_t *vis;
	int i;

	string = _ope_str(string);
	*nbw = _nbword(string, del);
	comm = _strtow(string, del);

	vis = NULL;
	aliascomm = _parse_alias(comm, nbw, param, vis, 0);

	if (*nbw > 0)
	{
		i = 1;
		while(aliascomm[i])
		{
			vis = NULL;
			if (_strcmp(aliascomm[i - 1],";") == 0)
				aliascomm = _parse_alias(aliascomm, nbw, param, vis, i);
			if (_strcmp(aliascomm[i - 1],"&&") == 0)
				aliascomm = _parse_alias(aliascomm, nbw, param, vis, i);
			if (_strcmp(aliascomm[i - 1],"||") == 0)
				aliascomm = _parse_alias(aliascomm, nbw, param, vis, i);
			i++;
		}
	}

/*	for (i = 0; i < *nbw; i++)
		printf("string[%i] is %s\n", i, aliascomm[i]);
*/

	return (aliascomm);
}





/**
 * _parse_alias - add all the alias in the
 * command line and update nbw
 *
 * @comm : intial command line
 * @nbw: total number of word in comm
 * @param: global parameter variable
 *
 * Return: new command line including alias
 */

char **_parse_alias(char **comm, int *nbw, param_t *param, aliasl_t *vis, int k)
{
	char *del = " \n\t\a\r\v";
	aliasl_t *head;
	int lenal, i;
	char **parsal;
	char **newcomm;

	if (comm[k] == NULL)
		return (NULL);
	head = param->alias;

	while (head)
	{
		if (_strcmp2(head->var, comm[k]) == 0 && _is_nodeal(vis, comm[k]) == 0)
		{
			_add_nodealias(&vis, comm[k]);
			lenal = _nbword(head->value, del);
			parsal = _strtow(head->value, del);
			newcomm = malloc((*nbw + lenal) * sizeof(char *));
			for (i = 0; i < k; i++)
			{
				newcomm[i] = _strdup(comm[i]);
				free(comm[i]);
			}
			for (i = 0; i < lenal; i ++)
			{
				newcomm[i + k] =_strdup(parsal[i]);
				free(parsal[i]);
			}
			for (i = 0; i < *nbw - k - 1; i++)
			{
				newcomm[i + k + lenal] = _strdup(comm[i + k + 1]);
				free(comm[i + k + 1]);
			}
			newcomm[*nbw + lenal - 1] = NULL;
			free(comm);
			free(parsal);
			*nbw = *nbw + lenal - 1;
			if (lenal == 0)
				return (newcomm);
			else
				return (_parse_alias(newcomm, nbw, param, vis, k));
		}
		head = head->next;
	}
	return (comm);

}

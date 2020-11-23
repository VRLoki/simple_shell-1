#include "hsh.h"


/**
 * _nbword2 - count number of words
 *
 * @s : string to be counted
 * @del : string of delimiters
 *
 * Return: number of words
 */

int _nbword2(const char *s, const char *del)
{
	int i = 0;
	int nbw = 1;

	if (s == NULL)
		return (0);

	while (s[i])
	{
		if (_isdelim(s[i], del) == 1)
			nbw++;
		i++;
	}

	return (nbw);
}



/**
 * _strtow2 - splits a string into words
 *
 * @str : string to be splitted
 * @del : string of delimiters
 *
 * Return: string
 */

char **_strtow2(const char *str, const char *del)
{
	int i = 0, nbw, sizeword = 0, curw = 0;
	char **s;

	nbw = _nbword2(str, del);

	s = malloc((nbw + 1) * sizeof(char *));
	if (s == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (_isdelim(str[i], del) == 1)
		{
			s[curw] = _mydup(str + i - sizeword, sizeword);
			curw += 1;
			sizeword = 0;
		}
		else
		{
			sizeword += 1;
		}
		i++;
	}

	if (_isdelim(str[i - 1], del) == 1)
	{
		s[curw] = 0;
		curw += 1;
	}
	else
	{
		s[curw] = _mydup(str + i - sizeword, sizeword);
		curw += 1;
	}
	s[nbw] = NULL;
	return (s);
}

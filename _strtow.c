#include "hsh.h"

/**
 * _isdelim - check if a character is a dleimiter
 *
 * @c : character to check
 * @del : string of delimiters
 *
 * Return: 1 if delimiter, else 0
 */

int _isdelim(char c, const char *del)
{
	int i = 0;

	if (del == NULL)
		return (0);

	while (del[i])
	{
		if (c == del[i])
			return (1);
		i++;
	}

	return (0);
}





/**
 * _nbword - count number of words
 *
 * @s : string to be counted
 * @del : string of delimiters
 *
 * Return: number of words
 */

int _nbword(const char *s, const char *del)
{
	int i = 1;
	int nbw = 0;

	if (s == NULL)
		return (0);

	if (_isdelim(s[0], del) == 0)
		nbw++;

	while (s[i])
	{
		if (_isdelim(s[i - 1], del) == 1 && _isdelim(s[i], del) == 0)
			nbw++;
		i++;
	}

	return (nbw);
}


/**
 * _mydup - duplicate a string
 *
 * @str : string to be copied
 * @size : size of string
 *
 * Return: string
 */

char *_mydup(const char *str, int size)
{
	char *s;
	int i;

	if (str == NULL)
		return (NULL);

	s = malloc((size + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}





/**
 * _strtow - splits a string into words
 *
 * @str : string to be splitted
 * @del : string of delimiters
 *
 * Return: string
 */

char **_strtow(const char *str, const char *del)
{
	int i = 0, nbw, inword = 0, sizeword = 0, curw = -1;
	char **s;

	nbw = _nbword(str, del);

	s = malloc((nbw + 1) * sizeof(char *));
	if (s == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (_isdelim(str[i], del) == 0 && inword == 0)
		{
			inword = 1;
			sizeword = 1;
			curw += 1;
		}
		else if (_isdelim(str[i], del) == 1 && inword == 1)
		{
			inword = 0;
			s[curw] = _mydup(str + i - sizeword, sizeword);
			sizeword = 0;
		}
		else if (_isdelim(str[i], del) == 0 && inword == 1)
			sizeword += 1;
		i++;
	}
	if (inword == 1)
	{
		s[curw] = _mydup(str + i - sizeword, sizeword);
	}
	s[curw + 1] = NULL;
	return (s);
}

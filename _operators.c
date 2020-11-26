#include "hsh.h"

/**
 * _ope_str - add space when operators
 *
 * @s : string to transform
 *
 * Return: transformed string
 */

char *_ope_str(char *s)
{
	char *new;

	new = _opeNEXT(s);
	new = _opeAND(new);
	new = _opeOR(new);
	new = _opeSTOP(new);
	return (new);
}




/**
 * _opeNEXT - add space when ';'
 *
 * @s : string to transform
 *
 * Return: transformed string
 */

char *_opeNEXT(char *s)
{
	int len = _strlen(s);
	int i = 0, j = 0;
	char *news;

	if (len <= 1)
		return (s);
	while (s[i])
	{
		if (s[i] == ';')
			len = len + 2;
		i++;
	}
	news = malloc((len + 1) * sizeof(char));
	i = 0;
	while (s[i])
	{
		if (s[i] == ';')
		{
			news[j] = ' ';
			news[j + 1] = ';';
			news[j + 2] = ' ';
			j = j + 3;
			i = i + 1;
		}
		else
		{
			news[j] = s[i];
			j = j + 1;
			i = i + 1;
		}
	}
	news[j] = '\0';
	free(s);
	return (news);
}



/**
 * _opeAND - add space when '&&'
 *
 * @s : string to transform
 *
 * Return: transformed string
 */

char *_opeAND(char *s)
{
	int len = _strlen(s);
	int i = 0, j = 0;
	char *news;

	if (len <= 2)
		return (s);
	while (s[i])
	{
		if (s[i] == '&' && s[i + 1] == '&')
		{
			len = len + 2;
			i = i + 1;
		}
		i++;
	}
	news = malloc((len + 1) * sizeof(char));
	i = 0;
	while (s[i])
	{
		if (s[i] == '&' && s[i + 1] == '&')
		{
			news[j] = ' ';
			news[j + 1] = '&';
			news[j + 2] = '&';
			news[j + 3] = ' ';
			j = j + 4;
			i = i + 2;
		}
		else
		{
			news[j] = s[i];
			j = j + 1;
			i = i + 1;
		}
	}
	news[j] = '\0';
	free(s);
	return (news);
}


/**
 * _opeOR - add space when '||'
 *
 * @s : string to transform
 *
 * Return: transformed string
 */

char *_opeOR(char *s)
{
	int len = _strlen(s);
	int i = 0, j = 0;
	char *news;

	if (len <= 2)
		return (s);
	while (s[i])
	{
		if (s[i] == '|' && s[i + 1] == '|')
		{
			len = len + 2;
			i = i + 1;
		}
		i++;
	}
	news = malloc((len + 1) * sizeof(char));
	i = 0;
	while (s[i])
	{
		if (s[i] == '|' && s[i + 1] == '|')
		{
			news[j] = ' ';
			news[j + 1] = '|';
			news[j + 2] = '|';
			news[j + 3] = ' ';
			j = j + 4;
			i = i + 2;
		}
		else
		{
			news[j] = s[i];
			j = j + 1;
			i = i + 1;
		}
	}
	news[j] = '\0';
	free(s);
	return (news);
}




/**
 * _opeSTOP - add space when '#'
 *
 * @s : string to transform
 *
 * Return: transformed string
 */

char *_opeSTOP(char *s)
{
	int len = _strlen(s);
	int i = 0, j = 0;
	char *news;

	if (len <= 1)
		return (s);
	while (s[i])
	{
		if (s[i] == '#')
			len = len + 2;
		i++;
	}
	news = malloc((len + 1) * sizeof(char));
	i = 0;
	while (s[i])
	{
		if (s[i] == '#')
		{
			news[j] = ' ';
			news[j + 1] = '#';
			news[j + 2] = ' ';
			j = j + 3;
			i = i + 1;
		}
		else
		{
			news[j] = s[i];
			j = j + 1;
			i = i + 1;
		}
	}
	news[j] = '\0';
	free(s);
	return (news);
}

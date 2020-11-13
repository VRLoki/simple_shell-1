#include "hsh.h"


/**
 * _strlennull - returns the length of a string
 *
 * @s : string
 *
 * Return: len of the String
 */

int _strlennull(char *s)
{
	int i = 0;

	if (s == NULL)
		return (0);

	while (*(s + i) != '\0')
		i++;

	return (i);
}


/**
 * _str_concat - concatenates two strings
 *
 * @s1 : first string
 * @s2 : second string
 *
 * Return: concatenated string
 */

char *_str_concat(char *s1, char *s2)
{
	char *s;
	int i;
	int strsize1, strsize2;

	strsize1 = _strlennull(s1);
	strsize2 = _strlennull(s2);

	s = malloc((strsize1 + strsize2 + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	for (i = 0; i < strsize1; i++)
		s[i] = s1[i];
	for (i = 0; i < strsize2; i++)
		s[i + strsize1] = s2[i];
	s[strsize1 + strsize2] = '\0';
	return (s);
}



/**
 * _getenv - get the value of an environment variable
 *
 * @name: string to find
 * @env : environment variable
 *
 * Return: pointer to string value of @key
 */
char *_getenv(char *name, char **env)
{
	int i = 0;

	while (env[i])
	{
		char *haystack = environ[i];
		char *needle = name;

		while (*haystack == *needle)
		{
			haystack++;
			needle++;
		}
		if (*needle == '\0')
			return (haystack + 1);
		i++;
	}
	return (NULL);
}






/**
 * _strrev - reverse a string.
 *
 * @str: the string.
 *
 * Return: reverse string
 */

char *_strrev(char *str)
{
	int i;
	int j;
	char *dest;

	if (str == NULL)
	{
		return (NULL);
	}
	j = _strlen(str);
	dest = (char *)malloc(sizeof(char) * j + 1);
	if (dest == NULL)
	{
		return (NULL);
	}
	j--;
	i = 0;
	while (j >= 0)
	{
		dest[i] = str[j];
		i++;
		j--;
	}
	dest[i] = '\0';
	if (str[i])
	{
		free(str);
	}
	return (dest);
}



/**
 * _convert_base - convert a number into any base
 *
 * @nbr: number to be converted
 * @base: conversion base
 * @cap: boolean for hexa convert for Capital print
 *
 * Return: converted number in string
 */

char *_convert_base(unsigned long int nbr, int base, int cap)
{
	char b16[] = "0123456789abcdef";
	char B16[] = "0123456789ABCDEF";
	char *result;
	int i;
	unsigned long int n;
	int count;

	if (nbr == 0)
	{
		result = (char *)malloc(sizeof(char) * 2);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	n = nbr;
	count = 0;
	while (n > 0)
	{
		n /= base;
		count++;
	}
	result = (char *)malloc(sizeof(char) * count + 1);
	if (result == NULL)
		return (NULL);
	n = nbr;
	i = 0;
	while (n != 0)
	{
		if (cap == 1)
			result[i] = B16[n % base];
		else
			result[i] = b16[n % base];
		n /= base;
		i++;
	}
	result[i] = '\0';
	return (_strrev(result));
}

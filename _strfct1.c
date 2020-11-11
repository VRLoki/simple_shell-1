#include "hsh.h"

/**
 * _strlen - returns the length of a string
 *
 * @s : string
 *
 * Return: len of the String
 */

int _strlen(char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
		i++;

	return (i);
}




/**
 * *_strcat - concatenates two strings
 *
 * @dest : destination
 * @src : string source to be concatenated
 *
 * Return: string concatenated
 */

char *_strcat(char *dest, char *src)
{
	int i, lendest, lensrc;

	lendest = _strlen(dest);
	lensrc = _strlen(src);

	for (i = 0; i <= lensrc; i++)
	{
		*(dest + i + lendest) = *(src + i);
	}
	*(dest + i + lendest) = '\0';

	return (dest);
}



/**
 * *_strcmp - compares two strings
 *
 * @s1 : first string
 * @s2 : second string
 *
 * Return: integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (*(s1 + i) == *(s2 + i) && *(s1 + i) && *(s2 + i))
		i++;

	return (*(s1 + i) - *(s2 + i));
}




/**
 * *_strcpy - copies a string to a buffer
 *
 * @dest : destination
 * @src : string source to be copied
 *
 * Return: string copied
 */

char *_strcpy(char *dest, char *src)
{
	int i, len;

	len = _strlen(src);

	for (i = 0; i <= len; i++)
	{
		*(dest + i) = *(src + i);
	}

	return (dest);
}





/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 *
 * @str : duplicated string
 *
 * Return: created array
 */

char *_strdup(char *str)
{
	char *s;
	int i;
	int strsize;

	if (str == NULL)
		return (NULL);

	strsize = _strlen(str);
	s = malloc((strsize + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	for (i = 0; i < strsize; i++)
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}

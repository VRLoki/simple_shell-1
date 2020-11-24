#include "hsh.h"


/**
 * _str_concat_f - concatenates two strings and free the first one.
 *
 * @s1 : first string
 * @s2 : second string
 *
 * Return: concatenated string
 */

char *_str_concat_f(char *s1, char *s2)
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
	if (s1 != NULL)
		free(s1);
	return (s);
}



/**
 * replace_null - replace the null character by space
 *
 * @buf : buffer read
 * @bufflen : size of the buffer
 *
 * Return: concatenated string
 */

void replace_null(char *buf, int bufflen)
{
	int i;

	for(i = 0; i < bufflen; i++)
	{
		if (buf[i] == '\0')
			buf[i] = ' ';
	}

}
